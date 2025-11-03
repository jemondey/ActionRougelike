// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_Thorns.h"
#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "SActionComponent.h"

USActionEffect_Thorns::USActionEffect_Thorns()
{
	Period = 0.f;
	Duration = 0.f;
	ReflectFraction = 0.2f;
	bAutoStart = true;
}

void USActionEffect_Thorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	USAttributeComponent* Attributes = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());
	if (Attributes)
	{
		Attributes->OnHealthChanged.AddDynamic(this, &USActionEffect_Thorns::OnHealthChanged);
	}
}

void USActionEffect_Thorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	USAttributeComponent* Attributes = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());
	if (Attributes)
	{
		Attributes->OnHealthChanged.RemoveDynamic(this, &USActionEffect_Thorns::OnHealthChanged);
	}
}

void USActionEffect_Thorns::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	AActor* OwningActor = GetOwningComponent()->GetOwner();

	if (InstigatorActor->GetClass() == OwningActor->GetClass())
	{
		return;
	}

	if (Delta < 0.f)
	{
		int32 DamageAmount = FMath::RoundToInt(Delta);
		DamageAmount = FMath::Abs(DamageAmount);
		USGameplayFunctionLibrary::ApplyDamage(OwningActor, InstigatorActor, DamageAmount);
	}
}