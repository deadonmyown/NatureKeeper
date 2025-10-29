#include "NatureKeeper/Public/IsometricCell.h"

#include "Components/BoxComponent.h"
#include "Interfaces/Visitor.h"


AIsometricCell::AIsometricCell()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AIsometricCell::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AIsometricCell::OnEndOverlap);
}

void AIsometricCell::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->UpdateOverlaps();
}

void AIsometricCell::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UVisitor>())
	{
		IVisitor::Execute_OnStartVisit(OtherActor, this);
	}
}

void AIsometricCell::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UVisitor>())
	{
		IVisitor::Execute_OnEndVisit(OtherActor, this);
	}
}



