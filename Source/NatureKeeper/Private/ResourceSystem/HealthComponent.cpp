#include "ResourceSystem/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::DecreaseResourceValue(int DeltaValue)
{
	if (CurrDamageInvincibleTime > 0.001f)
		return;
	
	Super::DecreaseResourceValue(DeltaValue);

	CurrDamageInvincibleTime = DamageInvincibleTime;
}

void UHealthComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (CurrDamageInvincibleTime == 0.0f)
		return;
	
	if (CurrDamageInvincibleTime > 0.001f)
		CurrDamageInvincibleTime -= DeltaTime;
	else
		CurrDamageInvincibleTime = 0.0f;
}


