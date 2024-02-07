// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_HealthPotion.h"
#include "SAttributeComponent.h"

void ASPowerup_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp && !AttributeComp->IsFullHealth())
	{
		AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax());
		HideAndCooldownPowerup();
	}
}
