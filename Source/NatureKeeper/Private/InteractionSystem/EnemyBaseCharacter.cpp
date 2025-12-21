#include "InteractionSystem/EnemyBaseCharacter.h"

#include "Components/SphereComponent.h"
#include "ResourceSystem/HealthComponent.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackDetectorCollision = CreateDefaultSubobject<USphereComponent>("AttackDetectorCollision");
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnResourceValueReachMin.AddDynamic(this, &AEnemyBaseCharacter::OnDeath);
}

void AEnemyBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrAttackDelay == 0.0f)
		return;

	if (CurrAttackDelay > 0.001f)
		CurrAttackDelay -= DeltaSeconds;
	else
		CurrAttackDelay = 0.0f;
}

void AEnemyBaseCharacter::Attack(TScriptInterface<UDamageable> DamageableActor)
{
	if (!CanAttack())
		return;
	
	if (!DamageableActor.GetObject())
		return;
	
	if (!DamageableActorTypes.Contains(IDamageable::Execute_GetDamageableType(DamageableActor.GetObject())))
		return;

	IDamageable::Execute_TakeDamage(DamageableActor.GetObject(), AttackDamage);

	CurrAttackDelay = AttackDelay;
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
