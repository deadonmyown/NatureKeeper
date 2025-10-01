// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FocusComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UFocusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFocusComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	bool bIsFocus = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	float FocusDistanceToPlayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	UPrimitiveComponent* FocusedComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	AActor* FocusedActor;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void UpdateFocus(bool bInIsFocus, float InDistanceToPlayer, UPrimitiveComponent* InFocusComponent, AActor* InFocusActor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void ClearFocus();
};
