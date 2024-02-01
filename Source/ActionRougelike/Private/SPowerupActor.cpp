// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ASPowerupActor::ASPowerupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere Comp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	CooldownAmount = 10.f;
}

// Called when the game starts or when spawned
void ASPowerupActor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ASPowerupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPowerupActor::Interact_Implementation(APawn* InstigatorPawn)
{
}

void ASPowerupActor::HideAndCooldownPowerup()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &ASPowerupActor::ShowActorAfterCooldown, CooldownAmount, false);
}

void ASPowerupActor::ShowActorAfterCooldown()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
