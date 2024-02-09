// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SGameModeBase.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ASGameModeBase();

	virtual void StartPlay() override;

protected:

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	void SpawnBotTimerElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UEnvQuery* SpawnBotQuery;

	UFUNCTION()
	void OnQueryFinished(class UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION(Exec)
	void KillAll();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	UCurveFloat* DifficultyCurve;

};
