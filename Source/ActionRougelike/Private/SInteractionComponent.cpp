// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "SWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("vm.InteractionDebugDraw"), false, TEXT("Draw Debug Lines/Spheres for Interaction Component"), ECVF_Cheat);

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TraceSphereRadius = 30.f;
	TraceDistance = 1000.f;
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindBestInteractable();
}

void USInteractionComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* Owner = GetOwner();
	FVector End;
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	FCollisionShape Shape;
	Shape.SetSphere(TraceSphereRadius);

	TArray<FHitResult> Hits;

	bool bHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, QueryParams, Shape);
	FColor Color = bHit ? FColor::Green : FColor::Red;

	FocusedActor = nullptr;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		if (DefaultWidgetInstance == nullptr && DefaultWidgetClass)
		{
			DefaultWidgetInstance = CreateWidget<USWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;
			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}

	if (CVarDebugDrawInteraction.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, Color, false, 3.f);
	}
}

void USInteractionComponent::PrimaryInteract()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	if(FocusedActor == nullptr)
	{
		return;
	}
	ISGameplayInterface::Execute_Interact(FocusedActor, MyPawn);
}