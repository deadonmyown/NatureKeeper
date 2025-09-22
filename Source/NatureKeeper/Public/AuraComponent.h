// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuraComponent.generated.h"


class UEffectBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UAuraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAuraComponent();

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Aura")
	TArray<UEffectBase*> Effects;

	virtual void BeginPlay() override;

public:
	
};
