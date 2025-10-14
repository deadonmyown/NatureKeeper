#include "Managers/WinEntityComponent.h"

UWinEntityComponent::UWinEntityComponent()
{
}


void UWinEntityComponent::ClearEntity()
{
	if (bIsClear)
		return;
	
	bIsClear = true;
	OnClearEntity.Broadcast(this);
}

void UWinEntityComponent::ReturnEntity()
{
	if (!bIsClear)
		return;
	
	bIsClear = false;
	OnReturnEntity.Broadcast(this);
}

void UWinEntityComponent::BeginPlay()
{
	Super::BeginPlay();	
}

