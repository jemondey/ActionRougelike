// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

void ASPlayerState::AddCredits(int32 Delta)
{
	if(Delta >= 0.0f)
	{
		Credits += Delta;
		OnCreditsChanged.Broadcast(this, Credits, Delta);
	}
}

bool ASPlayerState::RemoveCredits(int32 Delta)
{
	if (Delta >= 0.0f && Delta <= Credits)
	{
		Credits -= Delta;
		OnCreditsChanged.Broadcast(this, Credits, Delta);
		return true;
	}
	return false;
}
