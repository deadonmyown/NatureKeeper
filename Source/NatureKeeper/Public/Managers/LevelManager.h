#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

class ANaturalSpring;

UENUM(BlueprintType)
enum class ELevelPhase : uint8
{
	LP_Default UMETA(DisplayName = "Default"),
	LP_Final UMETA(DisplayName = "Final"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelPhaseChanged, ELevelPhase, NewLevelPhase);

UCLASS()
class NATUREKEEPER_API ALevelManager : public AActor
{
	GENERATED_BODY()

public:
	ALevelManager();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LevelManager")
	FOnLevelPhaseChanged OnLevelPhaseChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LevelManager")
	TArray<ANaturalSpring*> NaturalSprings; 

	UFUNCTION(BlueprintCallable, Category = "LevelManager")
	void OnLooseLevel();
	UFUNCTION(BlueprintCallable, Category = "LevelManager")
	void OnWinLevel();
	UFUNCTION(BlueprintCallable, Category = "LevelManager")
	void ChangeLevelPhase(const ELevelPhase& NewLevelPhase);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LevelManager")
	ELevelPhase GetLevelPhase() const {return CurrentLevelPhase;}
	
	UFUNCTION(BlueprintCallable, Category = "LevelManager")
	void RegisterNaturalSpring(ANaturalSpring* NewNaturalSpring);
	UFUNCTION(BlueprintCallable, Category = "LevelManager")
	void UnregisterNaturalSpring(ANaturalSpring* NaturalSpringToRemove);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LevelManager")
	TArray<UWorld*> WorldList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelManager")
	ELevelPhase CurrentLevelPhase = ELevelPhase::LP_Default;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEvilAbsorbComplete(ANaturalSpring* CompletedNaturalSpring);
};
