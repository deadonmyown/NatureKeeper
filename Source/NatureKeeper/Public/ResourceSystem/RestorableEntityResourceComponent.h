#pragma once

#include "CoreMinimal.h"
#include "EntityResourceComponent.h"
#include "RestorableEntityResourceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API URestorableEntityResourceComponent : public UEntityResourceComponent
{
	GENERATED_BODY()

public:
	URestorableEntityResourceComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Component")
	float RestoreDelayInSec = 2.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Component")
	int RestoreAmount = 10;

	FTimerHandle RestoreTimer;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRestore();
};
