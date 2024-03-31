// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()
	
public:

	USAction_ProjectileAttack();

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere, Category = "Attack")
	class UParticleSystem* CastEmitter;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float MaxRange = 10000;

	virtual void StartAction_Implementation(AActor* Instigator) override;

private:

	UFUNCTION()
	void ProjectileAttack_TimeElapsed(ACharacter* InstigatorCharacter);

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle_ProjectileAttack;

	bool bCanAttack;
	
};
