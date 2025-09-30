// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Affectable.h"
#include "AffectableComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UAffectableComponent : public UActorComponent, public IAffectable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAffectableComponent();

protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aura")
	TArray<UEffectBase*> Effects;
	
public:
	virtual bool RegisterEffect_Implementation(UEffectBase* EffectToAdd) override;
	virtual bool UnregisterEffect_Implementation(UEffectBase* EffectToRemove) override;
};
