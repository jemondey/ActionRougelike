// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API USActionEffect : public USAction
{
	GENERATED_BODY()

public:

	USActionEffect();

	void StartAction_Implementation(AActor* Instigator) override;
	void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect")
	float Period;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect")
	float Duration;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BLueprintNativeEvent, Category = "Effect")
	void ExecutePeriodicEffect(AActor* Instigator);
};
