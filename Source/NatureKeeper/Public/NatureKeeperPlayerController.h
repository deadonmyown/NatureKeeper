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
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;


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
	float FollowTime;
	
	

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	
	 
};


