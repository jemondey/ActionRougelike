// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"
#include "GameFramework/Character.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	//
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* InstigatorCharacter = Cast<ACharacter>(Instigator);
	InstigatorCharacter->PlayAnimMontage(AttackAnim);
	TimerDelegate.BindUFunction(this, FName("ProjectileAttack_TimeElapsed"), InstigatorCharacter);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ProjectileAttack, TimerDelegate, 0.2f, false);
}

void USAction_ProjectileAttack::ProjectileAttack_TimeElapsed(ACharacter* InstigatorCharacter)
{
	FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");
	FVector CameraStart = InstigatorCharacter->GetPawnViewLocation();
	FVector CameraEnd = CameraStart + (InstigatorCharacter->GetControlRotation().Vector() * MaxRange);
	FVector CameraPoint;
	FRotator Rotator;
	FHitResult HitRes;

	if (GetWorld()->LineTraceSingleByChannel(HitRes, CameraStart, CameraEnd, ECollisionChannel::ECC_Visibility))
	{
		CameraPoint = HitRes.ImpactPoint;
	}
	else
	{
		CameraPoint = CameraEnd;
	}
	Rotator = (CameraPoint - HandLocation).Rotation();
	FTransform SpawnTM = FTransform(Rotator, HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = InstigatorCharacter;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	StopAction(InstigatorCharacter);
}