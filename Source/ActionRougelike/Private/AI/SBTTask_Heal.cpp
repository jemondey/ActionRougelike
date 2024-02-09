// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!MyPawn)
	{
		return EBTNodeResult::Failed;
	}

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(MyPawn);
	if(AttributeComp)
	{
		AttributeComp->ApplyHealthChange(nullptr, AttributeComp->GetHealthMax());
	}

	return EBTNodeResult::Succeeded;
}
