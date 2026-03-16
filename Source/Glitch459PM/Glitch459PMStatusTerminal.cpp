#include "Glitch459PMStatusTerminal.h"

#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
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
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> BodyMaterial(TEXT("/Game/Horror/Materials/M_HorrorMetal.M_HorrorMetal"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> ScreenMaterial(TEXT("/Game/Horror/Materials/M_HorrorAccent.M_HorrorAccent"));
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

    ScreenGlow = CreateDefaultSubobject<UPointLightComponent>(TEXT("ScreenGlow"));
    ScreenGlow->SetupAttachment(SceneRoot);
    ScreenGlow->SetRelativeLocation(FVector(44.0f, 0.0f, 80.0f));
    ScreenGlow->SetIntensity(BaseGlowIntensity);
    ScreenGlow->SetLightColor(FColor(125, 255, 145));
    ScreenGlow->AttenuationRadius = 280.0f;
    ScreenGlow->SetCastShadows(false);

    TerminalAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("TerminalAudio"));
    TerminalAudio->SetupAttachment(SceneRoot);
    TerminalAudio->SetRelativeLocation(FVector(24.0f, 0.0f, 62.0f));
    TerminalAudio->bAutoActivate = true;
    TerminalAudio->SetVolumeMultiplier(0.16f);
    TerminalAudio->SetPitchMultiplier(0.85f);
    TerminalAudio->bAllowSpatialization = true;
    TerminalAudio->bOverrideAttenuation = true;
    TerminalAudio->AttenuationOverrides.bAttenuate = true;
    TerminalAudio->AttenuationOverrides.bSpatialize = true;
    TerminalAudio->AttenuationOverrides.AttenuationShapeExtents = FVector(80.0f, 0.0f, 0.0f);
    TerminalAudio->AttenuationOverrides.FalloffDistance = 900.0f;
    TerminalAudio->AttenuationOverrides.dBAttenuationAtMax = -36.0f;
    TerminalAudio->AttenuationOverrides.LPFRadiusMin = 100.0f;
    TerminalAudio->AttenuationOverrides.LPFRadiusMax = 900.0f;

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

    FlickerPhase += DeltaSeconds * FlickerSpeed;
    const float Flicker = 0.5f + 0.5f * FMath::Sin(FlickerPhase);
    const float Jitter = FMath::FRandRange(-0.08f, 0.08f);
    const float GlowIntensity = BaseGlowIntensity + (FlickerIntensityRange * (Flicker + Jitter));
    ScreenGlow->SetIntensity(FMath::Max(GlowIntensity, 120.0f));

    const float Green = FMath::Clamp(0.72f + (0.28f * Flicker), 0.6f, 1.0f);
    ScreenText->SetTextRenderColor(FLinearColor(0.52f, Green, 0.58f, 1.0f).ToFColor(true));

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
