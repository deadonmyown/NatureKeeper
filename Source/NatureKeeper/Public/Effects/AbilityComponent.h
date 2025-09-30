// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UAffectable;

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	AT_Good,
	AT_Evil
};

class UEffectFactory;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Aura")
	TArray<UEffectFactory*> GoodEffects;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Aura")
	TArray<UEffectFactory*> EvilEffects;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Aura")
	EAbilityType AuraType;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void ChangeAbilityEffectsFactory(EAbilityType NewType);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void ApplyAbilityEffect(const TScriptInterface<UAffectable>& InAffectedObject);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void UpdateAbilityEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void CancelAbilityEffect();

	UFUNCTION(BlueprintPure, Category = "Aura")
	TArray<UEffectFactory*>& GetActualEffects() { return AuraType == EAbilityType::AT_Good ? GoodEffects : EvilEffects; }
	UFUNCTION(BlueprintPure, Category = "Aura")
	EAbilityType GetActualAbilityType() const { return AuraType; }
};
