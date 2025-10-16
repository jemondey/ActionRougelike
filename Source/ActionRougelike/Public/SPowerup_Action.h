// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SAction.h"
#include "SPowerup_Action.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API ASPowerup_Action : public ASPowerupActor
{
	GENERATED_BODY()
	
public:

	ASPowerup_Action();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USAction> ActionClass;
};
