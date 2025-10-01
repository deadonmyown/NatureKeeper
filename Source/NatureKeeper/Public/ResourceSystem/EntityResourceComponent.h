#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EntityResourceComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceValueChanged, int, OldValue, int, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceValueReachMax, int, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceValueReachMin, int, MinValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UEntityResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntityResourceComponent();

	UPROPERTY(BlueprintAssignable, Category = "Resource Component")
	FOnResourceValueChanged OnResourceValueChanged;
	UPROPERTY(BlueprintAssignable, Category = "Resource Component")
	FOnResourceValueReachMax OnResourceValueReachMax;
	UPROPERTY(BlueprintAssignable, Category = "Resource Component")
	FOnResourceValueReachMin OnResourceValueReachMin;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Component")
	int ResourceValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Component")
	int MaxResourceValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource Component")
	int MinResourceValue;
	
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Resource Component")
	void SetResourceValue(int NewValue);
	UFUNCTION(BlueprintCallable, Category = "Resource Component")
	void IncreaseResourceValue(int DeltaValue);
	UFUNCTION(BlueprintCallable, Category = "Resource Component")
	void DecreaseResourceValue(int DeltaValue);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Resource Component")
	int GetResourceValue() const {return ResourceValue;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Resource Component")
	int GetMaxResourceValue() const {return MaxResourceValue;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Resource Component")
	int GetMinResourceValue() const {return MinResourceValue;}
};
