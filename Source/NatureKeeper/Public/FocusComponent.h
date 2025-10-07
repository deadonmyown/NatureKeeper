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

	UPROPERTY(BlueprintReadOnly, Category="Focus")
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float TraceUpdateTime = 0.5f;

	FTimerHandle TraceUpdateTimerHandle;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	bool bIsFocus = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	float FocusDistanceToActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	UPrimitiveComponent* FocusedComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	AActor* FocusedActor;

	UFUNCTION(BlueprintCallable, Category = "Focus")
	void UpdateTrace();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void UpdateFocus(bool bInIsFocus, float InDistanceToActor, UPrimitiveComponent* InFocusComponent, AActor* InFocusActor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void ClearFocus();
};
