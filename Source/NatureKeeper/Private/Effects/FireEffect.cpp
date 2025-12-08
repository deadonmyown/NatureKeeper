#include "Effects/FireEffect.h"

#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"

bool UFireEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;
	
	TArray<UEffectBase*> ObjectEffects = IAffectable::Execute_GetEffects(InAffectedObject.GetObject());

	bool bHasOppositeEffect = false;
	for (int i = ObjectEffects.Num() - 1; i >= 0; i--)
	{
		if (ObjectEffects[i]->EffectElementType == EEffectElement::EE_Water)
		{
			ObjectEffects[i]->CancelEffect();
			bHasOppositeEffect = true;
		}
	}

	if (bHasOppositeEffect)
	{
		TrySpawnVFX(SteamEffectVFX);
		
		TryDamage(SteamInitialDamageAmount);

		CancelEffect();

		UE_LOG(LogTemp, Display, TEXT("Fire Effect (Steam): %d"), SteamInitialDamageAmount);
		
		return true;
	}
	
	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Fire Effect: %d"), InitialDamageAmount);
	
	return true;
}
