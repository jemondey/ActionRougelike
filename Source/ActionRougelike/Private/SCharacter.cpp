// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &ASCharacter::Dash);
}

void ASCharacter::HealSelf(float Amount /* = 100 */)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	if (bCanAttack)
	{
		PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(CastEmitter, GetMesh(), TEXT("Muzzle_01"), FVector::ZeroVector, FRotator::ZeroRotator, FVector(0.4f), EAttachLocation::SnapToTarget);
		TimerDelegate.BindUFunction(this, FName("PrimaryAttack_TimeElapsed"), ProjectileClass);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack, TimerDelegate, 0.2f, false);
		bCanAttack = false;
	}
}

void ASCharacter::SecondaryAttack()
{
	if (bCanAttack)
	{
		PlayAnimMontage(AttackAnim);
		TimerDelegate.BindUFunction(this, FName("PrimaryAttack_TimeElapsed"), BlackholeClass);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack, TimerDelegate, 0.2f, false);
		bCanAttack = false;
	}
}

void ASCharacter::Dash()
{
	if (bCanAttack)
	{
		PlayAnimMontage(AttackAnim);
		TimerDelegate.BindUFunction(this, FName("PrimaryAttack_TimeElapsed"), DashClass);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack, TimerDelegate, 0.2f, false);
		bCanAttack = false;
	}
}

void ASCharacter::PrimaryAttack_TimeElapsed(TSubclassOf<AActor> SpawnClass)
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FVector CameraStart = CameraComp->GetComponentLocation();
	FVector CameraEnd = CameraStart + (CameraComp->GetForwardVector() * MaxRange);
	FVector CameraPoint;
	FRotator Rotator;
	FHitResult HitRes;

	if (GetWorld()->LineTraceSingleByChannel(HitRes, CameraStart, CameraEnd, ECollisionChannel::ECC_Visibility))
	{
		CameraPoint = HitRes.ImpactPoint;
	}
	else
	{
		CameraPoint = CameraEnd;
	}
	Rotator = (CameraPoint - HandLocation).Rotation();
	FTransform SpawnTM = FTransform(Rotator, HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnTM, SpawnParams);
	bCanAttack = true;
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}
