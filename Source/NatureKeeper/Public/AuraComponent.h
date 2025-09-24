// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuraComponent.generated.h"

UENUM(BlueprintType)
enum class EAuraType : uint8
{
	AT_Good,
	AT_Evil
};

class AAuraManager;
class UEffectBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UAuraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAuraComponent();

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Aura")
	TArray<UEffectBase*> EvilEffects;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Aura")
	TArray<UEffectBase*> GoodEffects;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Aura")
	EAuraType AuraType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aura")
	AAuraManager* AuraManager;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void ChangeAuraEffects(const EAuraType NewAuraType);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void ApplyAuraEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void UpdateAuraEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Aura")
	void CancelAuraEffect();
};
