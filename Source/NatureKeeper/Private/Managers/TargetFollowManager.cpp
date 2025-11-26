// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TargetFollowManager.h"


void ATargetFollowManager::AddTargetFollowMap(AActor* FollowActor, TScriptInterface<UTarget> FollowTarget)
{
	if (TargetFollowMap.Contains(FollowActor))
	{
		TargetFollowMap[FollowActor] = FollowTarget;
	}
	else
	{
		TargetFollowMap.Add(FollowActor, FollowTarget);
	}
}
