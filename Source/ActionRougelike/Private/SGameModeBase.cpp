// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"
#include "EngineUtils.h"
#include "SCharacter.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("vm.SpawnBots"), true, TEXT("Enable bot spawning"), ECVF_Cheat);

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
	bIsRespawning = false;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (QueryInstance)
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryFinished);
	}
}

void ASGameModeBase::OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}

	int32 NrOfAliveBots = 0;
	for (ASAICharacter* Bot : TActorRange<ASAICharacter>(GetWorld()))
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Bot);
		if (AttributeComp && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	float MaxBotAllowed = 10.f;
	if (ensure(DifficultyCurve))
	{
		MaxBotAllowed = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotAllowed)
	{
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}

void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	if (!bIsRespawning)
	{
		bIsRespawning = true;
		ASCharacter* Player = Cast<ASCharacter>(VictimActor);
		if (Player)
		{
			FTimerHandle TimerHandle_RespawnDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
			float RespawnRate = 5.0f;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnRate, false);
		}
	}
}

void ASGameModeBase::RespawnPlayerElapsed(AController* PlayerController)
{
	if (PlayerController)
	{
		PlayerController->UnPossess();
		RestartPlayer(PlayerController);
		bIsRespawning = false;
	}
}

void ASGameModeBase::KillAll()
{
	for (ASAICharacter* Bot : TActorRange<ASAICharacter>(GetWorld()))
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Bot);
		if (AttributeComp && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this);
		}
	}
}
