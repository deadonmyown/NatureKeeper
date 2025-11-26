#include "Effects/WindEffect.h"

#include "NatureKeeperGameMode.h"
#include "NatureKeeperUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "Managers/TargetFollowManager.h"

bool UWindEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!InAffectedObject.GetObject() || !EffectFactory || !InAffectedObject.GetObject()->Implements<UDamageable>())
		return false;

	if (IAffectable::Execute_GetResistEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType))
		return false;
	
	AffectedObject = InAffectedObject;
	EffectFactory->AddEffect(this);
	IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this);
	

	if (InitialDamageAmount > 0)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EffectVFX,
					IAffectable::Execute_GetEffectLocation(InAffectedObject.GetObject()),
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);
		
		IDamageable::Execute_TakeDamage(InAffectedObject.GetObject(), InitialDamageAmount);
	}

	if (AActor* AffectedActor = Cast<AActor>(InAffectedObject.GetObject()))
	{
		UNatureKeeperUtils::SetPlayerFocusComponentAsTarget(AffectedActor);
	}

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("AffectedObject: %s"), *InAffectedObject.GetObject()->GetName());
	UE_LOG(LogTemp, Display, TEXT("Effect factory: %s"), *EffectFactory->GetName());
	
	return true;
}

bool UWindEffect::CancelEffect()
{
	if (!AffectedObject.GetObject() || !EffectFactory)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);

		OnComplete.Broadcast();
		
		return false;
	}

	if (AActor* AffectedActor = Cast<AActor>(AffectedObject.GetObject()))
	{
		UNatureKeeperUtils::RemoveElementFromTargetFollowManager(AffectedActor);
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	EffectFactory->RemoveEffect(this);
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	EffectFactory = nullptr;
	
	OnComplete.Broadcast();
	
	return true;
}
