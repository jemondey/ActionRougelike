// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ACTIONROUGELIKE_API USAction : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool CanStart();
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning();
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	UWorld* GetWorld() const override;

protected:

	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTagContainer GrantsTags;
	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTagContainer BlockedTags;
	UFUNCTION(BlueprintCallable, Category = "Tags")
	USActionComponent* GetOwningComponent() const;

	bool bIsRunning;
};
