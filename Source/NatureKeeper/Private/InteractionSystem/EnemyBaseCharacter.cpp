#include "InteractionSystem/EnemyBaseCharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Managers/PhysicsManager.h"
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

	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;

	HealthComponent->OnResourceValueReachMin.AddDynamic(this, &AEnemyBaseCharacter::Death);
}

UPrimitiveComponent* AEnemyBaseCharacter::GetMainPrimitiveComponent_Implementation()
{
	return GetComponentByClass<UPrimitiveComponent>();
}

void AEnemyBaseCharacter::Revive_Implementation(int MaxValue)
{
	OnRevive(MaxValue);
}

void AEnemyBaseCharacter::Death_Implementation(int MinValue)
{
	OnDeath(MinValue);
}

void AEnemyBaseCharacter::OnRevive(int MaxValue)
{
	
}

void AEnemyBaseCharacter::OnDeath(int MinValue)
{
	GetWorld()->DestroyActor(this);
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

void AEnemyBaseCharacter::Heal_Implementation(int HealAmount)
{
	HealthComponent->IncreaseResourceValue(HealAmount);
}

void AEnemyBaseCharacter::TakeDamage_Implementation(int Damage, EEffectElement EffectElement, FVector DamageNormal)
{
	if (Execute_GetResistEffectElements(this).Contains(EffectElement))
		return;
	
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

void AEnemyBaseCharacter::StartSlow_Implementation(float InSlowPercent)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed * (1 - InSlowPercent);
}

void AEnemyBaseCharacter::StartStun_Implementation()
{
	StunCount++;
	
	StopCharacterLogic();
}

void AEnemyBaseCharacter::StopSlow_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
}

void AEnemyBaseCharacter::StopStun_Implementation()
{
	StunCount--;
	if (FreezeCount > 0 || StunCount > 0)
		return;
	
	StartCharacterLogic();
}

void AEnemyBaseCharacter::AddThrowImpulse_Implementation(UPrimitiveComponent* ThrowPrimitiveComponent, const FVector& InThrowDirection, const float InThrowStrength, const FThrowCommonParams& InParams)
{
	auto* Move = GetCharacterMovement();
	if (!Move) return;

	const float TimeNow = GetWorld()->TimeSeconds;

	if (TimeNow - LastKnockbackTime < InParams.Cooldown)
	{
		return;
	}
	LastKnockbackTime = TimeNow;

	FVector Dir = InThrowDirection.GetSafeNormal();

	if (!InParams.bAllowVertical)
	{
		Dir.Z = 0.f;
		Dir.Normalize();
	}

	const FVector Knockback = Dir * InThrowStrength;

	const bool bHasVertical = FMath::Abs(Knockback.Z) > 200.f;
	const bool bStrongHit = InThrowStrength >= InParams.LaunchThreshold;

	const bool bIsAI = Controller && Controller->IsA(AAIController::StaticClass());
	
	if ((bHasVertical || bStrongHit) && !bIsAI)
	{
		LaunchCharacter(Knockback, true, InParams.bAffectZOverride);
	}
	else
	{
		if(bIsAI)
			Move->StopActiveMovement();
		
		Move->AddImpulse(Knockback, InParams.bVelocityChange);

		const float Speed = Move->Velocity.Size();
		if (Speed > InParams.MaxSpeed)
		{
			Move->Velocity = Move->Velocity.GetSafeNormal() * InParams.MaxSpeed;
		}
	}
	if (!bIsAI)
	{
		Move->bForceMaxAccel = true;
	}
}

void AEnemyBaseCharacter::StartFreeze_Implementation()
{
	FreezeCount++;
	
	StopCharacterLogic();
}

void AEnemyBaseCharacter::StopFreeze_Implementation()
{
	FreezeCount--;
	if (FreezeCount > 0 || StunCount > 0)
		return;
	
	StartCharacterLogic();
}

void AEnemyBaseCharacter::StartCharacterLogic()
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		if (AIC->GetBrainComponent()->IsPaused())
			AIC->GetBrainComponent()->ResumeLogic("Stop stun/freeze");
		if (!AIC->GetBrainComponent()->IsRunning())
			AIC->GetBrainComponent()->StartLogic();
	}
}

void AEnemyBaseCharacter::StopCharacterLogic()
{
	GetCharacterMovement()->StopActiveMovement();
	GetCharacterMovement()->StopMovementImmediately();
	GetController()->StopMovement();
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Start stun/freeze");
	}
}
