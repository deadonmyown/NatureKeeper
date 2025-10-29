// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "NatureKeeperPlayerController.generated.h"

class UTargetComponent;
class UFocusComponent;
class ANatureKeeperCharacter;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerClickStarted);
// Triggered every frame when the input is held down
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerClickTriggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerClickStopped);

UCLASS()
class ANatureKeeperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANatureKeeperPlayerController();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerClickStarted OnPlayerClickStarted;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerClickTriggered OnPlayerClickTriggered;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerClickStopped OnPlayerClickStopped;
	
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Main Click Input Action (Usually LMB) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PrimaryClickAction;

	/** Secondary Click Input Action (Usually RMB) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SecondaryClickAction;

	UFUNCTION(BlueprintCallable, Category = Input)
	void StartLookAtCursor();
	UFUNCTION(BlueprintCallable, Category = Input)
	void StopLookAtCursor();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = Player)
	ANatureKeeperCharacter* NatureKeeperCharacter;
	UPROPERTY(BlueprintReadOnly, Category = Player)
	UFocusComponent* PlayerFocusComponent;
	UPROPERTY(BlueprintReadOnly, Category = Player)
	UTargetComponent* PlayerTargetComponent;
	
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	
	/** For how long it has been pressed */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	float TriggerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	bool bIsInteract;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	bool bLookAtCursor = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float LookAtCursorRotationSpeed = 5.0f;
	
	

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	
	void OnSecondaryInputStarted();
	void OnSecondaryInputStopped();
};


