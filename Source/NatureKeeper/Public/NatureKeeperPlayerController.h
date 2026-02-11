// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "NatureKeeperPlayerController.generated.h"

class UTargetStrategy;
struct FInputActionValue;
struct FInputActionInstance;
class UTargetComponent;
class UFocusComponent;
class ANatureKeeperCharacter;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerMainClickStarted);
// Triggered every frame when the input is held down
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMainClickTriggered, float, CurrTriggerTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMainClickStopped, float, StopTriggerTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerSecondaryClickStarted);
// Triggered every frame when the input is held down
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerSecondaryClickTriggered, float, CurrTriggerTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerSecondaryClickStopped, float, StopTriggerTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerThirdClickStarted);
// Triggered every frame when the input is held down
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerThirdClickTriggered, float, CurrTriggerTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerThirdClickStopped, float, StopTriggerTime);

UCLASS()
class ANatureKeeperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANatureKeeperPlayerController();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerMainClickStarted OnPlayerMainClickStarted;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerMainClickTriggered OnPlayerMainClickTriggered;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerMainClickStopped OnPlayerMainClickStopped;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerSecondaryClickStarted OnPlayerSecondaryClickStarted;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerSecondaryClickTriggered OnPlayerSecondaryClickTriggered;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerSecondaryClickStopped OnPlayerSecondaryClickStopped;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerThirdClickStarted OnPlayerThirdClickStarted;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerThirdClickTriggered OnPlayerThirdClickTriggered;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Input)
	FOnPlayerThirdClickStopped OnPlayerThirdClickStopped;
	
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	/** Main Click Input Action (Usually LMB) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PrimaryClickAction;

	/** Secondary Click Input Action (Usually RMB) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SecondaryClickAction;

	/** Third Click Input Action (Usually MMB) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ThirdClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TArray<UInputAction*> EffectsActions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TArray<UInputAction*> EffectTargetStrategiesActions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* EffectClearAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	float MovementDirectionDegreesAngle;

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
	float MainTriggerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	float SecondaryTriggerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	float ThirdTriggerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	bool bIsInteract;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	bool bLookAtCursor = true;
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
	void OnSecondaryInputTriggered();
	void OnSecondaryInputStopped();

	void OnThirdInputStarted();
	void OnThirdInputTriggered();
	void OnThirdInputStopped();

	void OnMove(const FInputActionValue& Value);
	void OnJump();
	void OnStopJumping();

	void OnStartInteraction();
	void OnEndInteraction();
	
	void OnEffectActions(const FInputActionInstance& Instance);
	void OnEffectTargetStrategiesActions(const FInputActionInstance& Instance);
	void OnEffectTargetStrategiesActionsByClass(TSubclassOf<UTargetStrategy> TargetStrategyClass);
	void OnEffectClear();
};


