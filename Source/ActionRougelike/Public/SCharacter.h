// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackholeClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float MaxRange = 10000;

	bool bCanAttack = true;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	class USInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USAttributeComponent* AttributeComp;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void SecondaryAttack();
	void Dash();
	UFUNCTION()
	void PrimaryAttack_TimeElapsed(TSubclassOf<AActor> SpawnClass);
	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle_PrimaryAttack;
	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};