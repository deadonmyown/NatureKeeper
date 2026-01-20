// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "NaturalSpring.generated.h"

class ALevelManager;
class ANaturalSpringPowerSource;
class ANatureKeeperCharacter;
class UEvilComponent;

//TODO: Later make a game event subsystem and translate event in this subsystem
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNaturalSpringEvilAbsorb, ANaturalSpring*, NaturalSpring, int, AbsorbedEvilAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNaturalSpringEvilAbsorbComplete, ANaturalSpring*, NaturalSpring);

UCLASS()
class NATUREKEEPER_API ANaturalSpring : public AInteractiveActor
{
	GENERATED_BODY()

public:
	ANaturalSpring();

	UPROPERTY(BlueprintAssignable, Category = "Natural Spring")
	FOnNaturalSpringEvilAbsorb OnNaturalSpringEvilAbsorb;
	UPROPERTY(BlueprintAssignable, Category = "Natural Spring")
	FOnNaturalSpringEvilAbsorbComplete OnNaturalSpringEvilAbsorbComplete;
protected:
	
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UEvilComponent* EvilComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Natural Spring")
	TArray<ANaturalSpringPowerSource*> NaturalSpringPowerSources;

	UPROPERTY()
	ALevelManager* LevelManagerCache;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Natural Spring")
	bool bIsAbsorbComplete;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Natural Spring")
	ANatureKeeperCharacter* InteractingPlayerCache;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Natural Spring")
	float EvilAbsorbTimeInSec = 1.0f;
	
	FTimerHandle EvilAbsorbTimer;

	UFUNCTION()
	void OnAbsorbComplete(int MinEvilValue);

	UFUNCTION()
	void OnAbsorbEvil();
	
	virtual void BeginPlay() override;

	bool CheckPowerSourcesConditions() const;
public:
	virtual bool StartInteract_Implementation(AActor* InteractionInvoker) override;
	virtual bool StopInteract_Implementation(AActor* InteractionInvoker) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Natural Spring")
	bool IsAbsorbComplete() const {return bIsAbsorbComplete;}
};
