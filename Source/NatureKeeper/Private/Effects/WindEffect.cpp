#include "Effects/WindEffect.h"

#include "NatureKeeperGameMode.h"
#include "NatureKeeperUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/WindEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/Follow.h"
#include "Managers/TargetFollowManager.h"

bool UWindEffect::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	UWindEffectDataAsset* WindEffectDataAsset = Cast<UWindEffectDataAsset>(InEffectDataAsset);

	if (!WindEffectDataAsset)
		return false;
	
	EffectVFX = WindEffectDataAsset->EffectVFX;
	EffectElementType = WindEffectDataAsset->EffectElementType;
	InitialDamageAmount = WindEffectDataAsset->InitialDamageAmount;
	TickDamageAmount = WindEffectDataAsset->TickDamageAmount;
	TicksCount = WindEffectDataAsset->TicksCount;
	TickAmount = WindEffectDataAsset->TickAmount;
	TickEffectVFX = WindEffectDataAsset->TickEffectVFX;

	CurrTick = 0;
	return true;
}

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
	if (!AffectedObject.GetObject())
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);

		UE_LOG(LogTemp, Warning, TEXT("[WindEffect] Affected Object Ptr is missing!"));
		OnFail.Broadcast(this);
		
		return false;
	}

	if (AffectedObject.GetObject()->Implements<UFollow>())
	{
		UNatureKeeperUtils::RemoveElementFromTargetFollowManager(AffectedObject.GetObject());
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	
	OnComplete.Broadcast(this);
	
	return true;
}
