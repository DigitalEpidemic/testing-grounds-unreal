// Copyright 2018 Jeffrey Polasz. All Rights Reserved.

#include "Mannequin.h"
#include "../Weapons/Gun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create first person Camera component
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent()); // Needs USceneComponent cast
	FPCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.0f); // Camera position
	FPCameraComponent->bUsePawnControlRotation = true;

	// Create Mesh component (First person view)
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPCharacterMesh"));
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->SetupAttachment(FPCameraComponent);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	FPMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	FPMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	if (GunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun Blueprint is missing!"));
		return;
	}

	// Spawn Gun
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(FPMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	Gun->AnimInstance = GetMesh()->GetAnimInstance();

	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::PullTrigger()
{
	Gun->OnFire();
}