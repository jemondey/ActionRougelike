// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	FVector WorldOffset;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	class AActor* AttachedActor;

protected:

	UPROPERTY(meta = (BindWidget))
	class USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
