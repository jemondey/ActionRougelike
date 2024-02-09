// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("vm.InteractionDebugDraw"), true, TEXT("Draw Debug Lines/Spheres for Interaction Component"), ECVF_Cheat);

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* Owner = GetOwner();
	FVector End;
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	End = EyeLocation + (EyeRotation.Vector() * 1000);

	//FHitResult HitRes;
	//GetWorld()->LineTraceSingleByObjectType(HitRes, EyeLocation, End, QueryParams);

	FCollisionShape Shape;
	Shape.SetSphere(30.f);

	TArray<FHitResult> Hits;

	bool bHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, QueryParams, Shape);
	FColor Color = bHit ? FColor::Green : FColor::Red;

	for(FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(Owner);
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				if(CVarDebugDrawInteraction.GetValueOnGameThread())
				{
					DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.f, 32, Color, false, 3.f);
				}
				break;
			}
		}
	}
	if(CVarDebugDrawInteraction.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, Color, false, 3.f);
	}
	
}