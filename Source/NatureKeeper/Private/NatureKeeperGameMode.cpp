// Copyright Epic Games, Inc. All Rights Reserved.

#include "NatureKeeper/Public/NatureKeeperGameMode.h"

#include "NatureKeeper/Public/NatureKeeperPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ANatureKeeperGameMode::ANatureKeeperGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ANatureKeeperPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/NatureKeeper/Blueprints/Player/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/NatureKeeper/Blueprints/Player/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ANatureKeeperGameMode::StartPlay()
{
	
	Super::StartPlay();
}
