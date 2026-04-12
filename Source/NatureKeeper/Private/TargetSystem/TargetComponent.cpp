#include "TargetSystem/TargetComponent.h"

#include "Effects/Ability.h"
#include "TargetSystem/TargetStrategy.h"
#include "ResourceSystem/ManaComponent.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickInterval = 0.5f;
	
	TargetStrategy = nullptr;
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Ability)
		Ability->InitAbility(GetOwner());
}

void UTargetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetStrategy && TargetStrategy->GetIsTargeting())
	{
		TargetStrategy->UpdateStrategy(DeltaTime);
	}
}

void UTargetComponent::StartTargetStrategy()
{
	if (!Ability)
		return;
	
	if (!Ability->CanCastAbility())
		return;
	
	if (!TargetStrategy)
	{
		TargetStrategy = DefaultTargetStrategy;
	}

	if (TargetStrategy->GetIsStarted())
	{
		TargetStrategy->CancelStrategy();
	}

	TargetStrategy->StartStrategy(Ability, this);
}

void UTargetComponent::SetTargetStrategy(UTargetStrategy* NewTargetStrategy)
{
	if (IsTargeting())
		return;
	
	if (TargetStrategy && TargetStrategy->GetIsStarted())
		ClearTargetStrategy();
	
	TargetStrategy = NewTargetStrategy;
	
	if(OnTargetSet.IsBound())
		OnTargetSet.Broadcast(TargetStrategy);
}

void UTargetComponent::ClearTargetStrategy()
{
	if (!TargetStrategy)
		return;

	if (IsTargeting())
		return;

	TargetStrategy->CancelStrategy();
	TargetStrategy = nullptr;

	if(OnTargetCancel.IsBound())
		OnTargetCancel.Broadcast();
}

void UTargetComponent::CancelTargetStrategy()
{
	if (!TargetStrategy)
		return;
	
	TargetStrategy->CancelStrategy();
	TargetStrategy = nullptr;
	
	ClearAbilityEffects();
	
	if(OnTargetCancel.IsBound())
		OnTargetCancel.Broadcast();
}

bool UTargetComponent::IsTargeting() const
{
	return TargetStrategy ? TargetStrategy->GetIsTargeting() : false;
}

void UTargetComponent::ClearAbilityEffects()
{
	if (!Ability)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is nullptr"));
		return;
	}

	if (IsTargeting())
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't modify ability because target strategy is targeting"));
		return;
	}

	Ability->ClearEffectDataAssets();
}

void UTargetComponent::AddAbilityEffect(UEffectDataAsset* DataAssetToAdd)
{
	if (!Ability)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is nullptr"));
		return;
	}

	if (IsTargeting())
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't modify ability because target strategy is targeting"));
		return;
	}
	
	if (!AvailableEffectDataAssets.Contains(DataAssetToAdd))
	{
		UE_LOG(LogTemp, Warning, TEXT("No such available effect data asset"));
		return;
	}

	Ability->AddEffectDataAssets(DataAssetToAdd);
}

void UTargetComponent::AddAbilityEffectByIndex(int32 EffectIndex)
{
	if (!AvailableEffectDataAssets.IsValidIndex(EffectIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect index is not valid %d"), EffectIndex);
		return;
	}

	UEffectDataAsset* DataAsset = AvailableEffectDataAssets[EffectIndex];

	if (!DataAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect data asset is nullptr"));
		return;
	}

	AddAbilityEffect(DataAsset);
}


