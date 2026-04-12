#include "Effects/WindEffect.h"

#include "NatureKeeperGameMode.h"
#include "NatureKeeperUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/WindEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/Follow.h"
#include "Interfaces/Throwable.h"
#include "Managers/PhysicsManager.h"
#include "Managers/TargetFollowManager.h"

bool UWindEffect::InitEffect(const FEffectData& InEffectData)
{
	const UWindEffectDataAsset* WindEffectDataAsset = Cast<UWindEffectDataAsset>(InEffectData.EffectDataAsset);

	if (!WindEffectDataAsset)
		return false;
	
	EffectVFX = WindEffectDataAsset->EffectVFX;
	EffectElementType = WindEffectDataAsset->EffectElementType;
	BlendingEffectDataMap = WindEffectDataAsset->BlendingEffectDataMap;
	InitialDamageAmount = WindEffectDataAsset->InitialDamageAmount;
	TickDamageAmount = WindEffectDataAsset->TickDamageAmount;
	TicksCount = WindEffectDataAsset->TicksCount;
	TickAmount = WindEffectDataAsset->TickAmount;
	TickEffectVFX = WindEffectDataAsset->TickEffectVFX;
	ThrowStrength = WindEffectDataAsset->ThrowStrength;
	ThrowNormal = InEffectData.EffectHitData.EffectImpactNormal;
	ThrowPrimitiveComponent = InEffectData.EffectHitData.EffectHitComponent;

	CurrTick = 0;
	return true;
}

bool UWindEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);

	if (InAffectedObject.GetObject()->Implements<UFollow>())
	{
		UNatureKeeperUtils::SetPlayerFocusComponentAsTarget(InAffectedObject.GetObject());
	}

	if (InAffectedObject.GetObject()->Implements<UThrowable>())
	{
		if (APhysicsManager* PM = UNatureKeeperUtils::GetPhysicsManager(this))
		{
			FVector FinalThrowVector = (-ThrowNormal + AdditionalThrowVector).GetSafeNormal();
			PM->ThrowActor(InAffectedObject.GetObject(), ThrowPrimitiveComponent, FinalThrowVector, ThrowStrength);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Tickable Damageable Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), InitialDamageAmount);
	
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
		UNatureKeeperUtils::RemoveElementFromTargetFollowMap(AffectedObject.GetObject());
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	
	OnComplete.Broadcast(this);
	
	return true;
}
