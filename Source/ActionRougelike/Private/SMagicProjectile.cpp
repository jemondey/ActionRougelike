// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SGameplayFunctionLibrary.h"
#include "SActionComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraShakeInnerRadius = 1000.f;
	CameraShakeOuterRadius = 5000.f;

	DamageAmount = 50.f;
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	AudioComp->Play();
}

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USActionComponent* ActionComp = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComp->Velocity = -MovementComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}


		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			FTransform SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, SpawnTransform);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
			UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShake, GetActorLocation(), CameraShakeInnerRadius, CameraShakeOuterRadius);
			
		}
		Destroy();
	}
}
