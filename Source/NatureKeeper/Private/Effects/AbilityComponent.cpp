#include "Effects/AbilityComponent.h"

#include "Effects/Ability.h"
#include "Effects/PlayerAbility.h"

UAbilityComponent::UAbilityComponent()
{
}

void UAbilityComponent::InitComponent(UManaComponent* InManaComponent)
{
	if (!InManaComponent) return;
	
	ManaComponent = InManaComponent;

	for (int i = 0; i < Abilities.Num(); i++)
	{
		if (Abilities[i])
			Abilities[i]->InitManaComponent(InManaComponent);
	}
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}
