// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CellMovable.h"
#include "NatureKeeperCharacter.generated.h"

class UCellMovementComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS(Blueprintable)
class ANatureKeeperCharacter : public ACharacter, public ICellMovable
{
	GENERATED_BODY()

public:
	ANatureKeeperCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCellMovementComponent* GetCellMovementComponent() const {return CellMovementComponent;}

private:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UCellMovementComponent* CellMovementComponent;
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	virtual TScriptInterface<UCellMovementInterface> GetCellMovementInterface_Implementation() override;
	virtual USceneComponent* GetNavigationRoot_Implementation() override;
	virtual bool TryMoveByCells_Implementation(ACell* TargetCell) override;
};

