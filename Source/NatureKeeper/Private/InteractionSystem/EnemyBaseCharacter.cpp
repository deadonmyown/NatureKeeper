#include "InteractionSystem/EnemyBaseCharacter.h"

#include "ResourceSystem/HealthComponent.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnResourceValueReachMin.AddDynamic(this, &AEnemyBaseCharacter::OnDeath);
}

void AEnemyBaseCharacter::OnDeath(int MinValue)
{
	GetWorld()->DestroyActor(this);
}

void AEnemyBaseCharacter::Heal_Implementation(int HealAmount)
{
	HealthComponent->IncreaseResourceValue(HealAmount);
}

void AEnemyBaseCharacter::TakeDamage_Implementation(int Damage)
{
	HealthComponent->DecreaseResourceValue(Damage);
}

bool AEnemyBaseCharacter::RegisterEffect_Implementation(UEffectBase* EffectToAdd)
{
	if (Effects.Contains(EffectToAdd))
		return false;

	Effects.Add(EffectToAdd);
	return true;
}

bool AEnemyBaseCharacter::UnregisterEffect_Implementation(UEffectBase* EffectToRemove)
{
	if (!Effects.Contains(EffectToRemove))
		return false;

	Effects.Remove(EffectToRemove);
	return true;
}

USceneComponent* AEnemyBaseCharacter::GetEffectLocation_Implementation()
{
	return GetRootComponent();
}
