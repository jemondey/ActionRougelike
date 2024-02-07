// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	HealthMax = 100.f;
	Health = HealthMax;
	
}

USAttributeComponent* USAttributeComponent::GetAtrributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<USAttributeComponent>();
	}
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAtrributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false;
}


// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	

	
}


// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0, HealthMax);
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);
	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float USAttributeComponent::GetHealth()
{
	return Health;
}

bool USAttributeComponent::IsFullHealth()
{
	return Health == HealthMax;
}

float USAttributeComponent::GetHealthMax()
{
	return HealthMax;
}

//float USAttributeComponent::GetHealth()
//{
//	return Health;
//}

