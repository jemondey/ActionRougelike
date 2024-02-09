// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

ASBlackholeProjectile::ASBlackholeProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(SphereComp);
}

void ASBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASBlackholeProjectile::OnActorOverlap);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASBlackholeProjectile::DestroySelf, 5.f, false);
}

void ASBlackholeProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	USAttributeComponent* ATR = USAttributeComponent::GetAtrributes(OtherActor);
	if (ATR && OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		ATR->ApplyHealthChange(GetInstigator(), -100.f);
	}
	else if(OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		OtherActor->Destroy();
	}
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