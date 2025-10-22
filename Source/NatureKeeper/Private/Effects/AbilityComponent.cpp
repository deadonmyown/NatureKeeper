#include "Effects/AbilityComponent.h"

#include "Effects/Ability.h"
#include "Effects/EffectBase.h"
#include "Effects/EffectFactory.h"
#include "TargetSystem/TargetStrategy.h"

UAbilityComponent::UAbilityComponent()
{
}

void UAbilityComponent::InitComponent(UManaComponent* InManaComponent)
{
	ManaComponent = InManaComponent;

	for (int i = 0; i < Abilities.Num(); i++)
	{
		if (Abilities[i])
			Abilities[i]->InitAbility(InManaComponent);
	}
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}
