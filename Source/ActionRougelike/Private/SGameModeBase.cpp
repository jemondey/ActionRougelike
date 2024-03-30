// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"
#include "EngineUtils.h"
#include "SCharacter.h"
#include "SPlayerState.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("vm.SpawnBots"), true, TEXT("Enable bot spawning"), ECVF_Cheat);

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
	bIsRespawning = false;
	CreditsPerKill = 100;
	DesiredPowerupCount = 10;
	RequiredPowerupDistance = 1000;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
	
	UEnvQueryInstanceBlueprintWrapper* PowerupQueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnPowerupQuery, this, EEnvQueryRunMode::AllMatching, nullptr);
	if (PowerupQueryInstance)
	{
		PowerupQueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryFinishedPowerupSpawn);
	}
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* BotQueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (BotQueryInstance)
	{
		BotQueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryFinishedBotSpawn);
	}
}

void ASGameModeBase::OnQueryFinishedBotSpawn(UEnvQueryInstanceBlueprintWrapper* BotQueryInstance, EEnvQueryStatus::Type BotQueryStatus)
{
	if (BotQueryStatus != EEnvQueryStatus::Success)
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

	TArray<FVector> Locations = BotQueryInstance->GetResultsAsLocations();
	if (Locations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}

void ASGameModeBase::OnQueryFinishedPowerupSpawn(UEnvQueryInstanceBlueprintWrapper* PowerupQueryInstance, EEnvQueryStatus::Type PowerupQueryStatus)
{
	if (PowerupQueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}

	TArray<FVector> Locations = PowerupQueryInstance->GetResultsAsLocations();
	TArray<FVector> UsedLocations;

	int32 NrOfSpawnedPowerups = 0;
	
	while (NrOfSpawnedPowerups < DesiredPowerupCount && Locations.Num() > 0)
	{
		int32 RandomLocationIndex = FMath::RandRange(0, Locations.Num() - 1);
		FVector PickedLocation = Locations[RandomLocationIndex];
		Locations.RemoveAt(RandomLocationIndex);

		bool bValidLocation = true;
		for (FVector OtherLocation : UsedLocations)
		{
			float Distance = (PickedLocation - OtherLocation).Size();
			if (Distance < RequiredPowerupDistance)
			{
				bValidLocation = false;
				break;
			}
		}

		if (!bValidLocation)
		{
			continue;
		}

		int32 RandomPowerupIndex = FMath::RandRange(0, PowerupClasses.Num() - 1);
		TSubclassOf<AActor> RandomPowerupClass = PowerupClasses[RandomPowerupIndex];
		PickedLocation = FVector(PickedLocation.X, PickedLocation.Y, PickedLocation.Z + 75);
		GetWorld()->SpawnActor<AActor>(RandomPowerupClass, PickedLocation, FRotator::ZeroRotator);
		UsedLocations.Add(PickedLocation);
		NrOfSpawnedPowerups++;
	}

}

void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	if (!bIsRespawning)
	{
		ASCharacter* Player = Cast<ASCharacter>(VictimActor);
		if (Player)
		{
			bIsRespawning = true;
			FTimerHandle TimerHandle_RespawnDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
			float RespawnRate = 5.0f;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnRate, false);
		}
	}

	APawn* KillerPawn = Cast<APawn>(Killer);
	if (KillerPawn)
	{
		if (ASPlayerState* PS = KillerPawn->GetPlayerState<ASPlayerState>())
		{
			PS->AddCredits(CreditsPerKill);
		}
	}
}

void ASGameModeBase::RespawnPlayerElapsed(AController* PlayerController)
{
	if (PlayerController)
	{
		PlayerController->UnPossess();
		RestartPlayer(PlayerController);
	}
	bIsRespawning = false;
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
