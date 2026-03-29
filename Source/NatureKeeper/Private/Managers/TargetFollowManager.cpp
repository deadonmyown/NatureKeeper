// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TargetFollowManager.h"


#include "Interfaces/Follow.h"
#include "Kismet/KismetMathLibrary.h"


ATargetFollowManager::ATargetFollowManager()
{
	PrimaryActorTick.bCanEverTick = true;
}