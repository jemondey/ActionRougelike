// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:

	ASDashProjectile();

protected:

	virtual void BeginPlay() override;

private:

	void StopSelf();
	void DashInstigator();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle Timer;
	UPROPERTY(EditAnywhere)
	UParticleSystem* DashExplodeParticle;
	
};
