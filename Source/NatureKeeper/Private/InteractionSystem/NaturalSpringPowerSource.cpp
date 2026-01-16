#include "InteractionSystem/NaturalSpringPowerSource.h"

#include "ResourceSystem/HealthComponent.h"


ANaturalSpringPowerSource::ANaturalSpringPowerSource()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsPowerSourceRevived = false;
}
void ANaturalSpringPowerSource::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent->GetResourceValue() == HealthComponent->GetMaxResourceValue())
		bIsPowerSourceRevived = true;
	
	HealthComponent->OnResourceValueReachMax.AddDynamic(this, &ANaturalSpringPowerSource::OnRevive);
}

void ANaturalSpringPowerSource::OnRevive(int MaxValue)
{
	bIsPowerSourceRevived = true;
}


void ANaturalSpringPowerSource::OnDeath(int MinValue)
{
	bIsPowerSourceRevived = false;
}

void ANaturalSpringPowerSource::TakeDamage_Implementation(int Damage, EEffectElement EffectElement,
                                                          FVector DamageNormal)
{
	Execute_Heal(this, Damage);
}

