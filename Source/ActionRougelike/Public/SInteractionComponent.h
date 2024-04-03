// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"

class USWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USInteractionComponent();

	void PrimaryInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FindBestInteractable();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USWorldUserWidget> DefaultWidgetClass;
	UPROPERTY()
	USWorldUserWidget* DefaultWidgetInstance;
	UPROPERTY()
	AActor* FocusedActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceSphereRadius;
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance;
};
