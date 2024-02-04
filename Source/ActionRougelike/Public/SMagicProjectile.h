// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()
	
public:	

	ASMagicProjectile();

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UParticleSystem* HitParticles;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	USoundBase* ImpactSound;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<UCameraShakeBase> CameraShake;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float CameraShakeInnerRadius;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float CameraShakeOuterRadius;

};
