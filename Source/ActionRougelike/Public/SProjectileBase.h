// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

UCLASS(ABSTRACT)
class ACTIONROUGELIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	

	ASProjectileBase();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* AudioComp;

public:	

	virtual void Tick(float DeltaTime) override;

};
