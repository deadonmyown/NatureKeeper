#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WinEntityComponent.generated.h"

//Delegate to remove entity from win manager, when all entities removed from win manager level complete
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClearEntity, UWinEntityComponent*, WinEntityComponent)
//Delegate to return entity in win manager, for any reason
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReturnEntity, UWinEntityComponent*, WinEntityComponent)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UWinEntityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWinEntityComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Win Entity")
	FOnClearEntity OnClearEntity;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Win Entity")
	FOnReturnEntity OnReturnEntity;

protected:
	virtual void BeginPlay() override;

};
