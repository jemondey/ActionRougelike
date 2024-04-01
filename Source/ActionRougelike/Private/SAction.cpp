// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "SActionComponent.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Action %s is running"), *ActionName.ToString());

	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Action %s is stopped"), *ActionName.ToString());

	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

UWorld* USAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if(Comp)
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}

bool USAction::CanStart()
{
	if (IsRunning())
	{
		return false;
	}

	USActionComponent* Comp = GetOwningComponent();
	if(Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

bool USAction::IsRunning()
{
	return bIsRunning;
}
