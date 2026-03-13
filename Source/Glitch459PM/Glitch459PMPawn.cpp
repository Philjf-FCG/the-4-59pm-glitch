#include "Glitch459PMPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"

AGlitch459PMPawn::AGlitch459PMPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(-10.0f, 0.0f, 64.0f));
    FirstPersonCamera->bUsePawnControlRotation = true;

    bUseControllerRotationYaw = true;

    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->bOrientRotationToMovement = false;
        MoveComp->MaxWalkSpeed = WalkSpeed;
    }
}

void AGlitch459PMPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGlitch459PMPawn::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGlitch459PMPawn::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AGlitch459PMPawn::StartSprint);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AGlitch459PMPawn::StopSprint);
}

void AGlitch459PMPawn::MoveForward(float Value)
{
    if (Controller && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AGlitch459PMPawn::MoveRight(float Value)
{
    if (Controller && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AGlitch459PMPawn::StartSprint()
{
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = SprintSpeed;
    }
}

void AGlitch459PMPawn::StopSprint()
{
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = WalkSpeed;
    }
}
