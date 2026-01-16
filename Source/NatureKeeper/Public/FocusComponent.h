// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Target.h"
#include "FocusComponent.generated.h"


class ANatureKeeperPlayerController;
class ANatureKeeperCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UFocusComponent : public UActorComponent, public ITarget
{
	GENERATED_BODY()

public:
	UFocusComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Focus")
	ANatureKeeperCharacter* PlayerRef;
	UPROPERTY(BlueprintReadOnly, Category="Focus")
	ANatureKeeperPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float TraceUpdateTime = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float PlayerTraceDistance = 200.0f;

	FTimerHandle TraceUpdateTimerHandle;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	bool bIsCursorFocus = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	float CursorFocusDistanceToActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	FVector CursorFocusHitCacheLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	UPrimitiveComponent* CursorFocusedComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	AActor* CursorFocusedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	bool bIsPlayerFocus = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	float PlayerFocusDistanceToActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	FVector PlayerFocusHitCacheLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	UPrimitiveComponent* PlayerFocusedComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	AActor* PlayerFocusedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
	FVector LookAtNormalized;

	UFUNCTION(BlueprintCallable, Category = "Focus")
	void UpdateTrace();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void UpdateCursorFocus(bool bInIsFocus, float InDistanceToActor, FVector InFocusHitLocation, UPrimitiveComponent* InFocusComponent, AActor* InFocusActor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void ClearCursorFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void UpdatePlayerFocus(bool bInIsFocus, float InDistanceToActor, FVector InFocusHitLocation, UPrimitiveComponent* InFocusComponent, AActor* InFocusActor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void ClearPlayerFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void GetPlayerLookAtNormalizedLocation(FVector& OutputResult);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void GetPlayerLookAtNormalized(FVector& OutputDirection);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	USceneComponent* GetPlayerMuzzleComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Focus")
	void GetPlayerCursorLookAtNormalized(FVector& OutputDirectionNormalized, FVector& OutputWorldLocation, FVector& OutputNormalizedWorldLocation);

	virtual FVector GetTargetLocation_Implementation() override;
	virtual FRotator GetTargetRotation_Implementation() override;
};
