

#include "InteractionSystem/DamageableInteractiveActor.h"

#include "ResourceSystem/HealthComponent.h"

ADamageableInteractiveActor::ADamageableInteractiveActor()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ADamageableInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnResourceValueReachMin.AddDynamic(this, &ADamageableInteractiveActor::OnDeath);
}

void ADamageableInteractiveActor::OnDeath(int MinValue)
{
	GetWorld()->DestroyActor(this);
}

void ADamageableInteractiveActor::Heal_Implementation(int HealAmount)
{
	HealthComponent->IncreaseResourceValue(HealAmount);
}

void ADamageableInteractiveActor::TakeDamage_Implementation(int Damage)
{
	HealthComponent->DecreaseResourceValue(Damage);
}

bool ADamageableInteractiveActor::RegisterEffect_Implementation(UEffectBase* EffectToAdd)
{
	if (Effects.Contains(EffectToAdd))
		return false;

	Effects.Add(EffectToAdd);
	return true;
}

bool ADamageableInteractiveActor::UnregisterEffect_Implementation(UEffectBase* EffectToRemove)
{
	if (!Effects.Contains(EffectToRemove))
		return false;

	Effects.Remove(EffectToRemove);
	return true;
}

FVector ADamageableInteractiveActor::GetEffectLocation_Implementation()
{
	return GetActorLocation();
}

