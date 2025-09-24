// Copyright Epic Games, Inc. All Rights Reserved.

#include "NatureKeeper/Public/NatureKeeperGameMode.h"

#include "AuraManager.h"
#include "Kismet/GameplayStatics.h"
#include "NatureKeeper/Public/NatureKeeperPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ANatureKeeperGameMode::ANatureKeeperGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ANatureKeeperPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ANatureKeeperGameMode::StartPlay()
{
	if (!AuraManager)
	{
		AuraManager = Cast<AAuraManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AuraManagerClass));
	}

	if (!AuraManager)
	{
		AuraManager = GetWorld()->SpawnActor<AAuraManager>(AuraManagerClass);
	}
	
	Super::StartPlay();
}
