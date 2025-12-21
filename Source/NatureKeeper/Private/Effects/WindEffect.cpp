#include "Effects/WindEffect.h"

#include "NatureKeeperGameMode.h"
#include "NatureKeeperUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/Follow.h"
#include "Managers/TargetFollowManager.h"

bool UWindEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);

	if (InAffectedObject.GetObject()->Implements<UFollow>())
	{
		UNatureKeeperUtils::SetPlayerFocusComponentAsTarget(InAffectedObject.GetObject());
	}

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Wind Effect: %d"), InitialDamageAmount);
	
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

	if (AffectedObject.GetObject()->Implements<UFollow>())
	{
		UNatureKeeperUtils::RemoveElementFromTargetFollowManager(AffectedObject.GetObject());
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	EffectFactory->RemoveEffect(this);
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	//EffectFactory = nullptr;
	
	OnComplete.Broadcast();
	
	return true;
}
