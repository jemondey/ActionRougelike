// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAtrributes(AActor* FromActor);
	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attributes")
	float Health;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attributes")
	float HealthMax;

public:	

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
	UFUNCTION(BlueprintCallable)
	float GetHealth();
	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);

	bool IsFullHealth();
	float GetHealthMax();
};
