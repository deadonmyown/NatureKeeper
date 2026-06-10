#pragma once

#include "CoreMinimal.h"
#include "DamageableInteractiveActor.h"
#include "TurretActor.generated.h"

class USphereComponent;

USTRUCT(BlueprintType, Blueprintable)
struct FTurretData
{
	GENERATED_BODY()

	FTurretData(): TurretActor(nullptr), bInFOV(false){}
	FTurretData(AActor* InTurretActor, bool bInInFOV = false): TurretActor(InTurretActor), bInFOV(bInInFOV){}


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* TurretActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bInFOV;

	bool operator==(const FTurretData& Other) const
	{
		return TurretActor == Other.TurretActor;
	}

	bool operator==(const AActor* Other) const
	{
		return TurretActor == Other;
	}
};

UCLASS()
class NATUREKEEPER_API ATurretActor : public ADamageableInteractiveActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurretActor();

protected:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	TArray<FTurretData> ActorsInRadius;

	/* from -1 (360 degree) to 1 (0 degree) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float FOVAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float SortPeriodInSec = 2.0f;

	float LastSortTime = 0.0f;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOtherActorDestroyed(AActor* OtherActor);

	void SortTurretData();
public:
	virtual void Tick(float DeltaTime) override;
	
};
