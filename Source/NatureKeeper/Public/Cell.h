#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "InteractionSystem/InteractiveActor.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Visitable.h"
#include "Cell.generated.h"


class UWinEntityComponent;
class UEvilComponent;

UCLASS()
class NATUREKEEPER_API ACell : public AActor, public IVisitable, public IAffectable	
{
	GENERATED_BODY()

public:
	ACell();

	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UEvilComponent* EvilComponent;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UWinEntityComponent* WinEntityComponent;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cell")
	TArray<UEffectBase*> Effects;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell")
	void OnMinEvilEnergyValueReach(int MinValue);

	UFUNCTION(BlueprintNativeEvent, Category = "Cell")
	USceneComponent* GetNavigationRoot();

	virtual bool StartVisit_Implementation(const TScriptInterface<UVisitor>& Visitor) override;
	virtual bool EndVisit_Implementation(const TScriptInterface<UVisitor>& Visitor) override;

	virtual bool RegisterEffect_Implementation(UEffectBase* EffectToAdd) override;
	virtual bool UnregisterEffect_Implementation(UEffectBase* EffectToRemove) override;
	virtual USceneComponent* GetEffectLocation_Implementation() override;
	virtual TArray<EEffectElement> GetWeaknessEffectElements_Implementation() override {return {};}
	virtual TArray<EEffectElement> GetResistEffectElements_Implementation() override {return {};}
	virtual TArray<UEffectBase*> GetEffects_Implementation() override {return Effects; }
};
