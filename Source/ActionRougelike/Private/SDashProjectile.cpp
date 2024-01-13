// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

ASDashProjectile::ASDashProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComp->ProjectileGravityScale = 0.f;
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectile::OnHit);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASDashProjectile::StopSelf, 0.4f, false);
}

void ASDashProjectile::StopSelf()
{
	MovementComp->StopMovementImmediately();

	//spawn particle effect
	FTransform SpawnTM = FTransform(GetActorRotation(), GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DashExplodeParticle, SpawnTM);

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASDashProjectile::DashInstigator, 0.2f, false);
}

void ASDashProjectile::DashInstigator()
{
	Destroy();

	GetInstigator()->TeleportTo(GetActorLocation(), GetActorRotation(), false);
}

void ASDashProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	StopSelf();
}
