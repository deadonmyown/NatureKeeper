#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraManager.generated.h"

class UAuraComponent;

UCLASS()
class NATUREKEEPER_API AAuraManager : public AActor
{
	GENERATED_BODY()

public:
	AAuraManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aura")
	TArray<UAuraComponent*> Auras;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Aura")
	TArray<AActor*> AffectedActors;
public:
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool RegisterAura(UAuraComponent* NewAura);
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool UnregisterAura(UAuraComponent* NewAura);
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool RegisterAffectedActor(AActor* NewActor);
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool UnregisterAffectedActor(AActor* NewActor);
};
