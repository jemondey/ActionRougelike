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

	if (InstigatorActor == OwningActor)
	{
		FString ErrMsg = "Should have been executed already";
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, ErrMsg);
		return;
	}

	if (!InstigatorActor)
	{
		FString ErrMsg1 = "NO INSTIGATOR!!!!";
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, ErrMsg1);
	}

	if (Delta < 0.f)
	{
		//FString ErrMsg1 = "Name of Instig: " + InstigatorActor->GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, ErrMsg1);
		int32 DamageAmount = FMath::RoundToInt(Delta /** ReflectFraction*/);
		DamageAmount = FMath::Abs(DamageAmount);
		USGameplayFunctionLibrary::ApplyDamage(OwningActor, InstigatorActor, DamageAmount);
		FString ErrMsg = "Should have been executed already";
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, ErrMsg);
	}
}