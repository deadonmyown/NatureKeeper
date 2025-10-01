// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/Ability.h"

#include "Effects/EffectBase.h"
#include "Effects/EffectFactory.h"
#include "TargetSystem/TargetStrategy.h"

void UAbility::Target_Implementation(UTargetComponent* InTargetComponent)
{
	if (!InTargetComponent)
		return;

	TargetStrategy->StartStrategy(this, InTargetComponent);
}

void UAbility::ApplyAbilityEffect_Implementation(const TScriptInterface<UAffectable>& InAffectedObject)
{
	TArray<UEffectFactory*> ActualEffectFactory = GetActualEffects();
	for (int i = 0; i < ActualEffectFactory.Num(); i++)
	{
		UEffectBase* NewEffect = ActualEffectFactory[i]->CreateEffect();
		NewEffect->ApplyEffect(InAffectedObject);
	}
}

/*void UAbility::CancelAbilityEffect_Implementation()
{
	TArray<UEffectFactory*> ActualEffectFactory = GetActualEffects();
	for (int i = 0; i < ActualEffectFactory.Num(); i++)
	{
		TArray<UEffectBase*> ActualEffects = ActualEffectFactory[i]->GetEffects();
		for (int j = ActualEffects.Num() - 1; j >= 0; j--)
		{
			ActualEffects[j]->CancelEffect();
		}
	}
}*/

void UAbility::ChangeAbilityEffectsFactory_Implementation(EAbilityType NewType)
{
	if (AbilityType == NewType)
		return;

	//CancelAbilityEffect();

	AbilityType = NewType;
}
