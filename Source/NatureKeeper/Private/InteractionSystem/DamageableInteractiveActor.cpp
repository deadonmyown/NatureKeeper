

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

	HealthComponent->OnResourceValueReachMin.AddDynamic(this, &ADamageableInteractiveActor::Death);
}

UPrimitiveComponent* ADamageableInteractiveActor::GetMainPrimitiveComponent_Implementation()
{
	return GetComponentByClass<UPrimitiveComponent>();
}

void ADamageableInteractiveActor::Revive_Implementation(int MaxValue)
{
	OnRevive(MaxValue);
}

void ADamageableInteractiveActor::Death_Implementation(int MinValue)
{
	OnDeath(MinValue);
}

void ADamageableInteractiveActor::OnRevive(int MaxValue)
{
	
}

void ADamageableInteractiveActor::OnDeath(int MinValue)
{
	GetWorld()->DestroyActor(this);
}

void ADamageableInteractiveActor::Heal_Implementation(int HealAmount)
{
	HealthComponent->IncreaseResourceValue(HealAmount);
}

void ADamageableInteractiveActor::TakeDamage_Implementation(int Damage, EEffectElement EffectElement,
	FVector DamageNormal)
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

USceneComponent* ADamageableInteractiveActor::GetEffectLocation_Implementation()
{
	return GetRootComponent();
}

void ADamageableInteractiveActor::AddThrowImpulse_Implementation(UPrimitiveComponent* ThrowPrimitiveComponent, const FVector& InThrowDirection, const float InThrowStrength, const FThrowCommonParams& InParams)
{
	if (!ThrowPrimitiveComponent)
	{
		ThrowPrimitiveComponent = GetMainPrimitiveComponent();
	}

	if (!ThrowPrimitiveComponent)
		return;

	if (ThrowPrimitiveComponent->IsSimulatingPhysics())
		ThrowPrimitiveComponent->AddImpulse(InThrowDirection * InThrowStrength);
}

void ADamageableInteractiveActor::StartFreeze_Implementation()
{
	//TODO: Change physical material in bps or in this cpp
	IFreezable::StartFreeze_Implementation();
}

void ADamageableInteractiveActor::StopFreeze_Implementation()
{
	IFreezable::StopFreeze_Implementation();
}

