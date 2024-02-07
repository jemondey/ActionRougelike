// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SBlackholeProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ASBlackholeProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:

	ASBlackholeProjectile();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class URadialForceComponent* ForceComp;
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	void DestroySelf();
	FTimerHandle Timer;

public:
	
	virtual void Tick(float DeltaTime) override;
	
};
