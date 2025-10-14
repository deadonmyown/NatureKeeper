#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinManager.generated.h"

class UWinEntityComponent;

UCLASS()
class NATUREKEEPER_API AWinManager : public AActor
{
	GENERATED_BODY()

public:
	AWinManager();

	UFUNCTION(BlueprintCallable, Category = "WinManager")
	void OnLooseLevel();
	UFUNCTION(BlueprintCallable, Category = "WinManager")
	void OnWinLevel();

	UFUNCTION(BlueprintCallable, Category = "WinManager")
	bool AddEntity(UWinEntityComponent* NewWinEntityComponent);
	UFUNCTION(BlueprintCallable, Category = "WinManager")
	bool RemoveEntity(UWinEntityComponent* ExistWinEntityComponent);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WinManager")
	TArray<UWinEntityComponent*> WinEntityComponents;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnClearEntity(UWinEntityComponent* ExistWinEntityComponent);
	UFUNCTION()
	void OnReturnEntity(UWinEntityComponent* NewWinEntityComponent);
};
