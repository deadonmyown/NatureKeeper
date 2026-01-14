// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/Ability.h"

#include "NatureKeeperUtils.h"
#include "Effects/EffectBase.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/AbilityDataAsset.h"
#include "Effects/Data/TickableDamageableEffectDataAsset.h"
#include "ResourceSystem/ManaComponent.h"
#include "TargetSystem/TargetStrategy.h"

void UAbility::ApplyAbilityEffect_Implementation(const TScriptInterface<UAffectable>& InAffectedObject)
{
	//We should check this before apply ability separately, because for example in projectile on hit we just invoke applyability method
	//and we don't care about mana, but to create this projectile we should spend ability mana
	/*if (!TrySpendMana())
		return;*/
	
	for (int i = 0; i < AbilityEffects.Num(); i++)
	{
		UEffectBase* NewEffect = AbilityEffects[i]->CreateEffect();
		NewEffect->ApplyEffect(InAffectedObject);
	}
}

bool UAbility::IsAbilityEffectsCompleted_Implementation()
{
	for (int i = 0; i < AbilityEffects.Num(); i++)
	{
		TArray<UEffectBase*> Effects = AbilityEffects[i]->GetEffects();
		if (Effects.Num() > 0)
			return false;
	}

	return true;
}

float UAbility::GetAbilityCompletionTime_Implementation()
{
	return UNatureKeeperUtils::GetEffectFactoriesCompletionTime(AbilityEffects);
	/*float CompletionTime = 0.0f;
	for (int i = 0; i < AbilityEffects.Num(); i++)
	{
		if (UTickableDamageableEffectDataAsset* TickableDataAsset = Cast<UTickableDamageableEffectDataAsset>(AbilityEffects[i]->GetEffectDataAsset()))
		{
			CompletionTime += TickableDataAsset->TicksCount * TickableDataAsset->TickAmount;
		}
	}
	
	return CompletionTime;*/
}

void UAbility::CancelAbilityEffect_Implementation()
{
	for (int i = 0; i < AbilityEffects.Num(); i++)
	{
		TArray<UEffectBase*> ActualEffects = AbilityEffects[i]->GetEffects();
		for (int j = ActualEffects.Num() - 1; j >= 0; j--)
		{
			ActualEffects[j]->CancelEffect();
		}
	}
}

void UAbility::InitManaComponent(UManaComponent* InManaComponent)
{
	ManaComponent = InManaComponent;
}

bool UAbility::CanCastAbility()
{
	//Can't cast ability if we have ability data asset, mana cost greater than zero and we didn't have enough mana or mana component is invalid
	if (AbilityDataAsset && AbilityDataAsset->AbilityManaCost > 0 &&
		(!ManaComponent || (ManaComponent->GetResourceValue() < AbilityDataAsset->AbilityManaCost)))
		return false;

	return true;
}

bool UAbility::TrySpendMana_Implementation()
{
	if (!CanCastAbility())
		return false;
	
	if (AbilityDataAsset && AbilityDataAsset->AbilityManaCost > 0)
		ManaComponent->DecreaseResourceValue(AbilityDataAsset->AbilityManaCost);

	return true;
}
