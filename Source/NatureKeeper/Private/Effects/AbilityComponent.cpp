#include "Effects/AbilityComponent.h"

#include "Effects/Ability.h"
#include "Effects/PlayerAbility.h"
#include "ResourceSystem/ManaComponent.h"

UAbilityComponent::UAbilityComponent()
{
}

void UAbilityComponent::SetAbilityTargetStrategy(UTargetStrategy* NewTargetStrategy)
{
	if (!PlayerAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is nullptr"));
		return;
	}

	PlayerAbility->SetTargetStrategy(NewTargetStrategy);
}

void UAbilityComponent::ClearAbilityTargetStrategy()
{
	if (!PlayerAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is nullptr"));
		return;
	}

	PlayerAbility->ClearTargetStrategy();
}

void UAbilityComponent::ClearAbilityEffects()
{
	if (!PlayerAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is nullptr"));
		return;
	}

	PlayerAbility->ClearEffectDataAssets();
}

void UAbilityComponent::AddAbilityEffect(UEffectDataAsset* DataAssetToAdd)
{
	if (!PlayerAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is nullptr"));
		return;
	}
	
	if (!AvailableEffectDataAssets.Contains(DataAssetToAdd))
	{
		UE_LOG(LogTemp, Warning, TEXT("No such available effect data asset"));
		return;
	}

	PlayerAbility->AddEffectDataAssets(DataAssetToAdd);
}

void UAbilityComponent::AddAbilityEffectByIndex(int32 EffectIndex)
{
	if (!AvailableEffectDataAssets.IsValidIndex(EffectIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect index is not valid %d"), EffectIndex);
		return;
	}

	PlayerAbility->AddEffectDataAssets(AvailableEffectDataAssets[EffectIndex]);
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerAbility) return;

	PlayerAbility->ClearTargetStrategy();
	if (UManaComponent* InManaComponent = GetOwner()->GetComponentByClass<UManaComponent>())
	{
		ManaComponent = InManaComponent;
		
		PlayerAbility->InitManaComponent(ManaComponent);
	}
}
