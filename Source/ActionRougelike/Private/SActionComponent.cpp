// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionComponent.h"
#include "SAction.h"


USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass)
{
	if (!ActionClass)
	{
		return;
	}

	USAction* NewAction = NewObject<USAction>(this, ActionClass);
	if (NewAction)
	{
		Actions.Add(NewAction);

		if (NewAction->bAutoStart && NewAction->CanStart())
		{
			NewAction->StartAction(Instigator);
		}
	}
}

void USActionComponent::RemoveAction(USAction* ActionToRemove)
{
	if (!(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		return;
	}

	Actions.Remove(ActionToRemove);
}

bool USActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart())
			{
				FString ErrMsg = "Failed to start action: " + ActionName.ToString();
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, ErrMsg);
				continue;
			}
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool USActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if(Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}


// Called when the game starts
void USActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (TSubclassOf<USAction> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
}


void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString Message = GetNameSafe(GetOwner()) + ": " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, Message);
}

