// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerup_Action.h"
#include "SActionComponent.h"

ASPowerup_Action::ASPowerup_Action()
{
	CooldownAmount = -1.f;
}

void ASPowerup_Action::Interact_Implementation(APawn* InstigatorPawn)
{
	USActionComponent* ActionComp = Cast<USActionComponent>(InstigatorPawn->FindComponentByClass(USActionComponent::StaticClass()));
	if (ActionComp)
	{
		if(!ActionComp->GetAction(ActionClass))
		{
			ActionComp->AddAction(InstigatorPawn, ActionClass);
			HideAndCooldownPowerup();
		}
	}
}
