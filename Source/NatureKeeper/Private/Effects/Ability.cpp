#include "Effects/Ability.h"

#include "NatureKeeperUtils.h"
#include "Effects/EffectBase.h"
#include "Effects/Data/TickableDamageableEffectDataAsset.h"
#include "ResourceSystem/ManaComponent.h"

void UAbility::ApplyAbilityEffect_Implementation(const TScriptInterface<UAffectable>& InAffectedObject)
{
	UNatureKeeperUtils::TryCreateAndApplyEffects(this, EffectDataAssets, InAffectedObject);
}

void UAbility::ClearEffectDataAssets()
{
	EffectDataAssets.Empty();

	if (OnEffectDataAssetClear.IsBound())
	{
		OnEffectDataAssetClear.Broadcast(this);
	}
}

void UAbility::AddEffectDataAssets(UEffectDataAsset* DataAssetToAdd)
{
	UEffectDataAsset* FinalDataAssetToAdd = DataAssetToAdd;
	
	if (!EffectDataAssets.IsEmpty() && DataAssetToAdd->BlendingEffectDataAsset)
	{
		for (int i = EffectDataAssets.Num() - 1; i >= 0; i--)
		{
			if (EffectDataAssets[i]->EffectElementType == DataAssetToAdd->BlendingEffectElementType)
			{
				FinalDataAssetToAdd = DataAssetToAdd->BlendingEffectDataAsset;
				EffectDataAssets.RemoveAt(i);
				break;
			}
		}
	}
	
	if (EffectDataAssets.Num() >= MaxEffectsAmount)
		return;
	
	EffectDataAssets.Add(FinalDataAssetToAdd);

	if (OnEffectDataAssetAdded.IsBound())
	{
		OnEffectDataAssetAdded.Broadcast(this, FinalDataAssetToAdd);
	}
}

void UAbility::RemoveEffectDataAssets(UEffectDataAsset* DataAssetToRemove)
{
	if (!EffectDataAssets.Contains(DataAssetToRemove))
		return;

	EffectDataAssets.RemoveSingle(DataAssetToRemove);

	if (OnEffectDataAssetRemoved.IsBound())
	{
		OnEffectDataAssetRemoved.Broadcast(this, DataAssetToRemove);
	}
	
	if (EffectDataAssets.IsEmpty())
	{
		if (OnEffectDataAssetClear.IsBound())
		{
			OnEffectDataAssetClear.Broadcast(this);
		}
	}
}

void UAbility::SetEffectDataAssets(const TArray<UEffectDataAsset*>& NewDataAssets)
{
	if (NewDataAssets.Num() > MaxEffectsAmount)
		return;
	
	EffectDataAssets = NewDataAssets;

	if (OnEffectDataAssetAdded.IsBound())
	{
		for (int i = 0; i < EffectDataAssets.Num(); i++)
		{
			OnEffectDataAssetAdded.Broadcast(this, EffectDataAssets[i]);
		}
	}
}

float UAbility::GetAbilityCompletionTime_Implementation()
{
	if (EffectDataAssets.IsEmpty())
		return 0.0f;
	
	float CompletionTime = 0.0f;
	for (int i = 0; i < EffectDataAssets.Num(); i++)
	{
		CompletionTime = FMath::Max(CompletionTime, EffectDataAssets[i]->GetEffectCompletionTime());
	}

	return CompletionTime;
}

void UAbility::InitManaComponent(UManaComponent* InManaComponent)
{
	ManaComponent = InManaComponent;
}

void UAbility::ChangeExtraManaCost(int32 DeltaCost)
{
	if (DeltaCost == 0)
		return;

	const int32 OldManaCost = ExtraManaCost;
	const int32 NewManaCost = FMath::Max(0,OldManaCost + DeltaCost);
	ExtraManaCost = NewManaCost;
}


bool UAbility::CanCastAbility()
{
	//Can't cast ability if mana cost greater than zero and we didn't have enough mana or mana component is invalid
	if (EffectDataAssets.IsEmpty() || !ManaComponent || (ManaComponent->GetResourceValue() < GetManaCost()))
		return false;

	return true;
}

int32 UAbility::GetManaCost()
{
	if (EffectDataAssets.IsEmpty())
		return 0;
	
	int32 CurrManaCost = ExtraManaCost;
	for (int i = 0; i < EffectDataAssets.Num(); i++)
	{
		CurrManaCost += EffectDataAssets[i]->EffectManaCost;
	}

	return CurrManaCost;
}

bool UAbility::TrySpendMana_Implementation()
{
	if (!CanCastAbility())
		return false;

	int32 ManaCost = GetManaCost();
	if (ManaComponent && ManaCost > 0)
		ManaComponent->DecreaseResourceValue(ManaCost);

	return true;
}
