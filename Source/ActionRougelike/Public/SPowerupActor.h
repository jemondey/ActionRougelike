// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerupActor.generated.h"


UCLASS()
class ACTIONROUGELIKE_API ASPowerupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	void HideAndCooldownPowerup();
	void ShowActorAfterCooldown();
	FTimerHandle CooldownTimer;
	UPROPERTY(EditAnywhere, Category = "Powerup")
	float CooldownAmount;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
