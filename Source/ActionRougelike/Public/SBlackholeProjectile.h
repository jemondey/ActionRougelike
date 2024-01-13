// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "SBlackholeProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API ASBlackholeProjectile : public ASMagicProjectile
{
	GENERATED_BODY()

public:

	ASBlackholeProjectile();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class URadialForceComponent* ForceComp;

private:

	void DestroySelf();
	FTimerHandle Timer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
