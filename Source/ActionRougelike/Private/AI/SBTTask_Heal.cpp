// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	if (AIC && BBC)
	{
		APawn* MyPawn = AIC->GetPawn();
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

		float Delta = AttributeComp->GetHealthMax() - AttributeComp->GetHealth();
		AttributeComp->ApplyHealthChange(nullptr, Delta);

		return EBTNodeResult::Succeeded;

		/*float MyHealth = AttributeComp->GetHealth();
		float MyMaxHealth = AttributeComp->GetHealthMax();
		bool bIsLowHealth = ((MyHealth / MyMaxHealth) * 100) <= LowHealth;
		BBC->SetValueAsBool("bIsLowHealth", bIsLowHealth);*/
	}
	return EBTNodeResult::Failed;
}
