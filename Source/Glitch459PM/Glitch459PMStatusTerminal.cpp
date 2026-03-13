#include "Glitch459PMStatusTerminal.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Glitch459PMGameMode.h"
#include "Engine/World.h"

AGlitch459PMStatusTerminal::AGlitch459PMStatusTerminal()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    TerminalBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalBody"));
    TerminalBody->SetupAttachment(SceneRoot);
    TerminalBody->SetRelativeScale3D(FVector(0.75f, 0.18f, 0.9f));

    ScreenText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScreenText"));
    ScreenText->SetupAttachment(SceneRoot);
    ScreenText->SetRelativeLocation(FVector(24.0f, 0.0f, 34.0f));
    ScreenText->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    ScreenText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Left);
    ScreenText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextTop);
    ScreenText->SetWorldSize(11.0f);
    ScreenText->SetTextRenderColor(FColor(125, 255, 145));
    ScreenText->SetText(FText::FromString(FallbackText));
}

void AGlitch459PMStatusTerminal::BeginPlay()
{
    Super::BeginPlay();
    RefreshScreen();
}

void AGlitch459PMStatusTerminal::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    TimeSinceRefresh += DeltaSeconds;
    if (TimeSinceRefresh >= RefreshInterval)
    {
        TimeSinceRefresh = 0.0f;
        RefreshScreen();
    }
}

void AGlitch459PMStatusTerminal::RefreshScreen()
{
    UWorld* World = GetWorld();
    AGlitch459PMGameMode* GameMode = World ? Cast<AGlitch459PMGameMode>(World->GetAuthGameMode()) : nullptr;
    const FString DisplayText = GameMode ? GameMode->GetTerminalStatusText() : FallbackText;
    ScreenText->SetText(FText::FromString(DisplayText));
}
