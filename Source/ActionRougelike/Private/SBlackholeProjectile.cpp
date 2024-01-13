// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ASBlackholeProjectile::ASBlackholeProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(SphereComp);
}

void ASBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASBlackholeProjectile::DestroySelf, 5.f, false);
}

void ASBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForceComp->FireImpulse();
}

void ASBlackholeProjectile::DestroySelf()
{
	Destroy();
}