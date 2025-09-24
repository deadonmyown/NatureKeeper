// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CellMovable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/Visitor.h"
#include "NatureKeeperCharacter.generated.h"

class AAuraManager;
class UEffectBase;
class UHealthComponent;
class UCellMovementComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS(Blueprintable)
class ANatureKeeperCharacter : public ACharacter, public ICellMovable, public IVisitor, public IDamageable
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
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UHealthComponent* HealthComponent;
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Aura from player that affecting cells on visit to transform from fel aura (negative black aura) to light (positive aura)*/
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TArray<UEffectBase*> PlayerAuraEffects;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aura")
	AAuraManager* AuraManager;
	
	virtual TScriptInterface<UCellMovementInterface> GetCellMovementInterface_Implementation() override;
	virtual USceneComponent* GetNavigationRoot_Implementation() override;
	virtual bool TryMoveByCells_Implementation(ACell* TargetCell) override;

	virtual bool OnStartVisit_Implementation(TScriptInterface<UVisitable> Visitable) override;
	virtual bool OnEndVisit_Implementation(TScriptInterface<UVisitable> Visitable) override;
};

