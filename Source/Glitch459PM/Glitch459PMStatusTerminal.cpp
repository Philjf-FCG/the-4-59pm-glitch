#include "Glitch459PMStatusTerminal.h"

#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Glitch459PMGameMode.h"
#include "Engine/World.h"
#include "Materials/MaterialInterface.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"

AGlitch459PMStatusTerminal::AGlitch459PMStatusTerminal()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> BodyMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> ScreenMaterial(TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));
    static ConstructorHelpers::FObjectFinder<USoundBase> TerminalSound(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue.CompileSuccess_Cue"));

    TerminalPedestal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalPedestal"));
    TerminalPedestal->SetupAttachment(SceneRoot);
    TerminalPedestal->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
    TerminalPedestal->SetRelativeScale3D(FVector(0.25f, 0.28f, 0.6f));

    TerminalBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalBody"));
    TerminalBody->SetupAttachment(SceneRoot);
    TerminalBody->SetRelativeLocation(FVector(26.0f, 0.0f, 68.0f));
    TerminalBody->SetRelativeScale3D(FVector(0.48f, 0.3f, 0.34f));

    TerminalScreen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalScreen"));
    TerminalScreen->SetupAttachment(SceneRoot);
    TerminalScreen->SetRelativeLocation(FVector(48.0f, 0.0f, 72.0f));
    TerminalScreen->SetRelativeScale3D(FVector(0.04f, 0.26f, 0.24f));

    TerminalKeyboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalKeyboard"));
    TerminalKeyboard->SetupAttachment(SceneRoot);
    TerminalKeyboard->SetRelativeLocation(FVector(16.0f, 0.0f, 48.0f));
    TerminalKeyboard->SetRelativeScale3D(FVector(0.28f, 0.28f, 0.04f));

    ScreenText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScreenText"));
    ScreenText->SetupAttachment(SceneRoot);
    ScreenText->SetRelativeLocation(FVector(51.0f, 0.0f, 83.0f));
    ScreenText->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    ScreenText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Left);
    ScreenText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextTop);
    ScreenText->SetWorldSize(7.8f);
    ScreenText->SetTextRenderColor(FColor(125, 255, 145));
    ScreenText->SetText(FText::FromString(FallbackText));

    TerminalAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("TerminalAudio"));
    TerminalAudio->SetupAttachment(SceneRoot);
    TerminalAudio->SetRelativeLocation(FVector(24.0f, 0.0f, 62.0f));
    TerminalAudio->bAutoActivate = true;
    TerminalAudio->SetVolumeMultiplier(0.16f);
    TerminalAudio->SetPitchMultiplier(0.85f);

    if (CubeMesh.Succeeded())
    {
        TerminalPedestal->SetStaticMesh(CubeMesh.Object);
        TerminalBody->SetStaticMesh(CubeMesh.Object);
        TerminalScreen->SetStaticMesh(CubeMesh.Object);
        TerminalKeyboard->SetStaticMesh(CubeMesh.Object);
    }

    if (BodyMaterial.Succeeded())
    {
        TerminalPedestal->SetMaterial(0, BodyMaterial.Object);
        TerminalBody->SetMaterial(0, BodyMaterial.Object);
        TerminalKeyboard->SetMaterial(0, BodyMaterial.Object);
    }

    if (ScreenMaterial.Succeeded())
    {
        TerminalScreen->SetMaterial(0, ScreenMaterial.Object);
    }

    if (TerminalSound.Succeeded())
    {
        TerminalAudio->SetSound(TerminalSound.Object);
    }
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
