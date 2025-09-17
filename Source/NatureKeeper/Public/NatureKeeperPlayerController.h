// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/CellMovableController.h"
#include "NatureKeeperPlayerController.generated.h"

class AIsometricCell;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ANatureKeeperPlayerController : public APlayerController, public ICellMovableController
{
	GENERATED_BODY()

public:
	ANatureKeeperPlayerController();

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

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

protected:
	UPROPERTY()
	ACell* CurrentMovingToCell;
	UPROPERTY()
	ACell* CurrentTargetCell;
	UPROPERTY()
	int32 CurrentMovingToCellIndex;
	UPROPERTY()
	TArray<ACell*> CurrentPath;
	
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	virtual ACell* GetCellMovingTo_Implementation() override;
	virtual int32 GetCellMovingToIndex_Implementation() override;
	virtual ACell* GetTargetCell_Implementation() override;
	virtual TArray<ACell*> GetPath_Implementation() override;
	virtual void StartActiveMoveByPath_Implementation(TArray<ACell*> NewPath) override;
	virtual void StopActiveMoveByPath_Implementation() override;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


