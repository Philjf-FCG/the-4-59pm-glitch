#include "Glitch459PMPlayerController.h"

#include "Glitch459PMGameMode.h"
#include "Engine/World.h"

void AGlitch459PMPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly());
}

void AGlitch459PMPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent);
    InputComponent->BindAction(TEXT("NextObject"), IE_Pressed, this, &AGlitch459PMPlayerController::OnNextObject);
    InputComponent->BindAction(TEXT("PrevObject"), IE_Pressed, this, &AGlitch459PMPlayerController::OnPrevObject);
    InputComponent->BindAction(TEXT("NextExit"), IE_Pressed, this, &AGlitch459PMPlayerController::OnNextExit);
    InputComponent->BindAction(TEXT("PrevExit"), IE_Pressed, this, &AGlitch459PMPlayerController::OnPrevExit);
    InputComponent->BindAction(TEXT("NextTask"), IE_Pressed, this, &AGlitch459PMPlayerController::OnNextTask);
    InputComponent->BindAction(TEXT("PrevTask"), IE_Pressed, this, &AGlitch459PMPlayerController::OnPrevTask);
    InputComponent->BindAction(TEXT("Inspect"), IE_Pressed, this, &AGlitch459PMPlayerController::OnInspect);
    InputComponent->BindAction(TEXT("FlagAnomaly"), IE_Pressed, this, &AGlitch459PMPlayerController::OnFlagAnomaly);
    InputComponent->BindAction(TEXT("CompleteTask"), IE_Pressed, this, &AGlitch459PMPlayerController::OnCompleteTask);
    InputComponent->BindAction(TEXT("UseExit"), IE_Pressed, this, &AGlitch459PMPlayerController::OnUseExit);
}

AGlitch459PMGameMode* AGlitch459PMPlayerController::GetGlitchGameMode() const
{
    UWorld* World = GetWorld();
    return World ? Cast<AGlitch459PMGameMode>(World->GetAuthGameMode()) : nullptr;
}

void AGlitch459PMPlayerController::OnNextObject()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->SelectNextObject();
    }
}

void AGlitch459PMPlayerController::OnPrevObject()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->SelectPreviousObject();
    }
}

void AGlitch459PMPlayerController::OnNextExit()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->SelectNextExit();
    }
}

void AGlitch459PMPlayerController::OnPrevExit()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->SelectPreviousExit();
    }
}

void AGlitch459PMPlayerController::OnNextTask()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->SelectNextTask();
    }
}

void AGlitch459PMPlayerController::OnPrevTask()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->SelectPreviousTask();
    }
}

void AGlitch459PMPlayerController::OnInspect()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->GetSelectedObjectDescriptionAndClue();
    }
}

void AGlitch459PMPlayerController::OnFlagAnomaly()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->TryFlagSelectedObject();
    }
}

void AGlitch459PMPlayerController::OnCompleteTask()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->TryCompleteSelectedTask();
    }
}

void AGlitch459PMPlayerController::OnUseExit()
{
    if (AGlitch459PMGameMode* GameMode = GetGlitchGameMode())
    {
        GameMode->TryUseSelectedExit();
    }
}
