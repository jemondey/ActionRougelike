// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* AudioComp;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	USoundBase* ImpactSound;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<UCameraShakeBase> CameraShake;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float CameraShakeInnerRadius;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float CameraShakeOuterRadius;

};
