#include "InteractionSystem/EnemyBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ResourceSystem/HealthComponent.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackDetectorCollision = CreateDefaultSubobject<USphereComponent>("AttackDetectorCollision");
	AttackDetectorCollision->SetupAttachment(GetCapsuleComponent());
	AttackDetectorCollision->SetSphereRadius(100.f);
	AttackDetectorCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackDetectorCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackDetectorCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
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

bool AEnemyBaseCharacter::StartAttack_Implementation()
{
	if (!CanAttack()) return false;
	
	bIsAttacking = true;
	return true;
}

void AEnemyBaseCharacter::EndAttack_Implementation()
{
	bIsAttacking = false;
	CurrAttackDelay = AttackDelay;
}

void AEnemyBaseCharacter::Attack(const TScriptInterface<UDamageable>& DamageableActor, int InDamage)
{
	AActor* DamagedActor = Cast<AActor>(DamageableActor.GetObject());

	if (!DamagedActor) return;
	
	if (!DamageableActor.GetObject())
		return;
	
	if (!DamageableActorTypes.Contains(IDamageable::Execute_GetDamageableType(DamageableActor.GetObject())))
		return;
	
	FVector DamageNormal = (GetActorLocation() - DamagedActor->GetActorLocation()).GetSafeNormal();
	DamageNormal.Z = 0.0f;
	IDamageable::Execute_TakeDamage(DamageableActor.GetObject(), InDamage, EEffectElement::EE_Physical, DamageNormal);
}

void AEnemyBaseCharacter::OnDeath(int MinValue)
{
	GetWorld()->DestroyActor(this);
}

void AEnemyBaseCharacter::Heal_Implementation(int HealAmount)
{
	HealthComponent->IncreaseResourceValue(HealAmount);
}

void AEnemyBaseCharacter::TakeDamage_Implementation(int Damage, EEffectElement EffectElement, FVector DamageNormal)
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
