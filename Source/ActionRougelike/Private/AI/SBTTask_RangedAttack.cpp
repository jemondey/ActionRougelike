// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		ACharacter* MyPawn = Cast<ACharacter>(AIController->GetPawn());
		if (!MyPawn)
		{
			return EBTNodeResult::Failed;
		}
		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if(!TargetActor)
		{
			return EBTNodeResult::Failed;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();
		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
		NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
