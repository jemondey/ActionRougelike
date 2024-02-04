// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"

USBTService_CheckHealth::USBTService_CheckHealth()
{
	LowHealth = 20;
}

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	if (AIC && BBC)
	{
		APawn* MyPawn = AIC->GetPawn();
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

		float MyHealth = AttributeComp->GetHealth();
		float MyMaxHealth = AttributeComp->GetHealthMax();
		bool bIsLowHealth = ((MyHealth / MyMaxHealth) * 100) <= LowHealth;
		BBC->SetValueAsBool("bIsLowHealth", bIsLowHealth);
	}
}
