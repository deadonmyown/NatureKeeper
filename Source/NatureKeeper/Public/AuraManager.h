#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraManager.generated.h"

class UAffectable;
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
	TArray<TScriptInterface<UAffectable>> AffectedObjects;
public:
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool RegisterAura(UAuraComponent* NewAura);
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool UnregisterAura(UAuraComponent* AuraToRemove);
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool RegisterAffectedObject(TScriptInterface<UAffectable> NewObject);
	UFUNCTION(BlueprintCallable, Category = "Aura")
	bool UnregisterAffectedObject(TScriptInterface<UAffectable> NewObject);

	UFUNCTION(BlueprintCallable, Category = "Aura")
	TArray<TScriptInterface<UAffectable>> GetAffectedObjects() const {return AffectedObjects;}
};
