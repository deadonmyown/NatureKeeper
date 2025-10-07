// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NatureKeeperPlayerController.h"
#include "GameFramework/Character.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/CellMovable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/Visitor.h"
#include "NatureKeeperCharacter.generated.h"

class ANatureKeeperPlayerController;
class UFocusComponent;
class UTargetComponent;
class UAbilityComponent;
class UEvilComponent;
class UManaComponent;
class AAuraManager;
class UEffectBase;
class UHealthComponent;
class UCellMovementComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS(Blueprintable)
class ANatureKeeperCharacter : public ACharacter, public ICellMovable, public IVisitor, public IDamageable, public IAffectable
{
	GENERATED_BODY()

public:
	ANatureKeeperCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCellMovementComponent* GetCellMovementComponent() const {return CellMovementComponent;}

protected:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UCellMovementComponent* CellMovementComponent;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UAbilityComponent* AbilityComponent;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UTargetComponent* TargetComponent;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UHealthComponent* HealthComponent;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UManaComponent* ManaComponent;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UEvilComponent* EvilComponent;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UFocusComponent* FocusComponent;
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damageable")
	EDamageableType DamageableType = EDamageableType::DT_GoodPlayer;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	UTargetComponent* GetTargetComponent() const {return TargetComponent;}
	UFUNCTION(BlueprintCallable, Category = "Player")
	UFocusComponent* GetFocusComponent() const {return FocusComponent;}
	UFUNCTION(BlueprintCallable, Category = "Player")
	ANatureKeeperPlayerController* GetNatureKeeperController() const {return Cast<ANatureKeeperPlayerController>(GetController());}
	
	virtual TScriptInterface<UCellMovementInterface> GetCellMovementInterface_Implementation() override;
	virtual USceneComponent* GetNavigationRoot_Implementation() override;
	virtual bool TryMoveByCells_Implementation(ACell* TargetCell) override;

	virtual bool OnStartVisit_Implementation(const TScriptInterface<UVisitable>& Visitable) override;
	virtual bool OnEndVisit_Implementation(const TScriptInterface<UVisitable>& Visitable) override;

	virtual void Heal_Implementation(int HealAmount) override;
	virtual void TakeDamage_Implementation(int Damage) override;
	virtual EDamageableType GetDamageableType_Implementation() override {return DamageableType; }
};

