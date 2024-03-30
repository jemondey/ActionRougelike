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

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* PlayerController);

protected:

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	void SpawnBotTimerElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UEnvQuery* SpawnBotQuery;

	UFUNCTION()
	void OnQueryFinishedBotSpawn(class UEnvQueryInstanceBlueprintWrapper* BotQueryInstance, EEnvQueryStatus::Type BotQueryStatus);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	UCurveFloat* DifficultyCurve;

	UFUNCTION(Exec)
	void KillAll();

	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
	class UEnvQuery* SpawnPowerupQuery;

	UFUNCTION()
	void OnQueryFinishedPowerupSpawn(class UEnvQueryInstanceBlueprintWrapper* PowerupQueryInstance, EEnvQueryStatus::Type PowerupQueryStatus);

	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
	TArray<TSubclassOf<AActor>> PowerupClasses;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	int32 DesiredPowerupCount;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	float RequiredPowerupDistance;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 CreditsPerKill;

	bool bIsRespawning;

};
