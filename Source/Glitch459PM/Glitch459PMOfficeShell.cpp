#include "Glitch459PMOfficeShell.h"

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

AGlitch459PMOfficeShell::AGlitch459PMOfficeShell()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> WallMaterial(TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> FloorMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
    static ConstructorHelpers::FObjectFinder<USoundBase> AmbientSound(TEXT("/Engine/EditorSounds/Notifications/CompileStart_Cue.CompileStart_Cue"));

    Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    Floor->SetupAttachment(SceneRoot);

    Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ceiling"));
    Ceiling->SetupAttachment(SceneRoot);

    NorthWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NorthWall"));
    NorthWall->SetupAttachment(SceneRoot);

    SouthWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SouthWall"));
    SouthWall->SetupAttachment(SceneRoot);

    EastWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EastWall"));
    EastWall->SetupAttachment(SceneRoot);

    WestWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WestWall"));
    WestWall->SetupAttachment(SceneRoot);

    Desk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Desk"));
    Desk->SetupAttachment(SceneRoot);

    RoomLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RoomLabel"));
    RoomLabel->SetupAttachment(SceneRoot);

    ObjectLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ObjectLabel"));
    ObjectLabel->SetupAttachment(SceneRoot);

    ExitLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ExitLabel"));
    ExitLabel->SetupAttachment(SceneRoot);

    DirectiveLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DirectiveLabel"));
    DirectiveLabel->SetupAttachment(SceneRoot);

    OverheadLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("OverheadLight"));
    OverheadLight->SetupAttachment(SceneRoot);

    FocusLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FocusLight"));
    FocusLight->SetupAttachment(SceneRoot);

    RoomAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("RoomAudio"));
    RoomAudio->SetupAttachment(SceneRoot);
    RoomAudio->bAutoActivate = true;
    RoomAudio->SetVolumeMultiplier(0.28f);
    RoomAudio->SetPitchMultiplier(0.6f);
    RoomAudio->bAllowSpatialization = true;
    RoomAudio->bOverrideAttenuation = true;
    RoomAudio->AttenuationOverrides.bAttenuate = true;
    RoomAudio->AttenuationOverrides.bSpatialize = true;
    RoomAudio->AttenuationOverrides.AttenuationShapeExtents = FVector(420.0f, 0.0f, 0.0f);
    RoomAudio->AttenuationOverrides.FalloffDistance = 2200.0f;
    RoomAudio->AttenuationOverrides.dBAttenuationAtMax = -24.0f;
    RoomAudio->AttenuationOverrides.LPFRadiusMin = 320.0f;
    RoomAudio->AttenuationOverrides.LPFRadiusMax = 2200.0f;

    if (CubeMesh.Succeeded())
    {
        Floor->SetStaticMesh(CubeMesh.Object);
        Ceiling->SetStaticMesh(CubeMesh.Object);
        NorthWall->SetStaticMesh(CubeMesh.Object);
        SouthWall->SetStaticMesh(CubeMesh.Object);
        EastWall->SetStaticMesh(CubeMesh.Object);
        WestWall->SetStaticMesh(CubeMesh.Object);
        Desk->SetStaticMesh(CubeMesh.Object);
    }

    if (WallMaterial.Succeeded())
    {
        NorthWall->SetMaterial(0, WallMaterial.Object);
        SouthWall->SetMaterial(0, WallMaterial.Object);
        EastWall->SetMaterial(0, WallMaterial.Object);
        WestWall->SetMaterial(0, WallMaterial.Object);
        Ceiling->SetMaterial(0, WallMaterial.Object);
    }

    if (FloorMaterial.Succeeded())
    {
        Floor->SetMaterial(0, FloorMaterial.Object);
        Desk->SetMaterial(0, FloorMaterial.Object);
    }

    if (AmbientSound.Succeeded())
    {
        RoomAudio->SetSound(AmbientSound.Object);
    }

    ConfigureSurface(Floor, FVector(0.0f, 0.0f, -10.0f), FVector(12.0f, 12.0f, 0.2f));
    ConfigureSurface(Ceiling, FVector(0.0f, 0.0f, 420.0f), FVector(12.0f, 12.0f, 0.2f));
    ConfigureSurface(NorthWall, FVector(0.0f, 600.0f, 200.0f), FVector(12.0f, 0.2f, 4.2f));
    ConfigureSurface(SouthWall, FVector(0.0f, -600.0f, 200.0f), FVector(12.0f, 0.2f, 4.2f));
    ConfigureSurface(EastWall, FVector(600.0f, 0.0f, 200.0f), FVector(0.2f, 12.0f, 4.2f));
    ConfigureSurface(WestWall, FVector(-600.0f, 0.0f, 200.0f), FVector(0.2f, 12.0f, 4.2f));
    ConfigureSurface(Desk, FVector(280.0f, 0.0f, 42.0f), FVector(1.8f, 0.9f, 0.5f));

    RoomLabel->SetRelativeLocation(FVector(280.0f, -180.0f, 110.0f));
    RoomLabel->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    RoomLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    RoomLabel->SetText(FText::FromString(TEXT("BREAKROOM LOOP TEST")));
    RoomLabel->SetWorldSize(48.0f);
    RoomLabel->SetTextRenderColor(FColor(255, 235, 180));

    ObjectLabel->SetRelativeLocation(FVector(-320.0f, -240.0f, 112.0f));
    ObjectLabel->SetRelativeRotation(FRotator(0.0f, 35.0f, 0.0f));
    ObjectLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Left);
    ObjectLabel->SetText(FText::FromString(TEXT("OBJECT")));
    ObjectLabel->SetWorldSize(28.0f);
    ObjectLabel->SetTextRenderColor(FColor(175, 215, 255));

    ExitLabel->SetRelativeLocation(FVector(420.0f, 250.0f, 112.0f));
    ExitLabel->SetRelativeRotation(FRotator(0.0f, -145.0f, 0.0f));
    ExitLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Left);
    ExitLabel->SetText(FText::FromString(TEXT("EXIT")));
    ExitLabel->SetWorldSize(28.0f);
    ExitLabel->SetTextRenderColor(FColor(165, 255, 205));

    DirectiveLabel->SetRelativeLocation(FVector(0.0f, -520.0f, 220.0f));
    DirectiveLabel->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    DirectiveLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    DirectiveLabel->SetText(FText::FromString(TEXT("DIRECTIVE")));
    DirectiveLabel->SetWorldSize(24.0f);
    DirectiveLabel->SetTextRenderColor(FColor(255, 220, 170));

    OverheadLight->SetRelativeLocation(FVector(0.0f, 0.0f, 320.0f));
    OverheadLight->SetIntensity(12000.0f);
    OverheadLight->SetLightColor(FColor(255, 244, 214));
    OverheadLight->AttenuationRadius = 2600.0f;

    FocusLight->SetRelativeLocation(FVector(-150.0f, -40.0f, 150.0f));
    FocusLight->SetIntensity(2400.0f);
    FocusLight->SetLightColor(FColor(145, 210, 255));
    FocusLight->AttenuationRadius = 460.0f;
    FocusLight->SetCastShadows(false);

    RoomAudio->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
}

void AGlitch459PMOfficeShell::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    RefreshAtmosphere(DeltaSeconds);
}

void AGlitch459PMOfficeShell::ConfigureSurface(UStaticMeshComponent* MeshComponent, const FVector& RelativeLocation, const FVector& RelativeScale, const FRotator& RelativeRotation) const
{
    if (!MeshComponent)
    {
        return;
    }

    MeshComponent->SetRelativeLocation(RelativeLocation);
    MeshComponent->SetRelativeRotation(RelativeRotation);
    MeshComponent->SetRelativeScale3D(RelativeScale);
    MeshComponent->SetMobility(EComponentMobility::Movable);
}

void AGlitch459PMOfficeShell::RefreshAtmosphere(float DeltaSeconds)
{
    UWorld* World = GetWorld();
    AGlitch459PMGameMode* GameMode = World ? Cast<AGlitch459PMGameMode>(World->GetAuthGameMode()) : nullptr;
    if (!GameMode)
    {
        return;
    }

    AtmospherePhase += DeltaSeconds * (1.2f + (0.35f * GameMode->GetPressureLevel()));
    const float Flicker = 0.5f + (0.5f * FMath::Sin(AtmospherePhase));
    const float PressureAlpha = static_cast<float>(GameMode->GetPressureLevel()) / 5.0f;

    const float LightIntensity = 9000.0f + (2600.0f * Flicker) - (2200.0f * PressureAlpha);
    OverheadLight->SetIntensity(FMath::Max(LightIntensity, 4200.0f));

    const FLinearColor CalmColor(1.0f, 0.96f, 0.84f);
    const FLinearColor PanicColor(1.0f, 0.74f, 0.62f);
    const FLinearColor MixedColor = FMath::Lerp(CalmColor, PanicColor, PressureAlpha);
    OverheadLight->SetLightColor(MixedColor.ToFColor(true));

    const FString LabelText = FString::Printf(TEXT("%s\nPressure %d/5"), *GameMode->GetCurrentRoomName().ToUpper(), GameMode->GetPressureLevel());
    RoomLabel->SetText(FText::FromString(LabelText));
    RoomLabel->SetTextRenderColor(FMath::Lerp(FLinearColor(1.0f, 0.92f, 0.7f), FLinearColor(1.0f, 0.58f, 0.58f), PressureAlpha).ToFColor(true));

    ObjectLabel->SetText(FText::FromString(FString::Printf(TEXT("OBJECT\n%s"), *GameMode->GetSelectedObjectName().ToUpper())));
    ObjectLabel->SetTextRenderColor(FMath::Lerp(FLinearColor(0.68f, 0.86f, 1.0f), FLinearColor(0.95f, 0.7f, 0.7f), PressureAlpha).ToFColor(true));

    ExitLabel->SetText(FText::FromString(FString::Printf(TEXT("EXIT\n%s"), *GameMode->GetSelectedExitLabel().ToUpper())));
    ExitLabel->SetTextRenderColor(FMath::Lerp(FLinearColor(0.72f, 1.0f, 0.84f), FLinearColor(1.0f, 0.78f, 0.62f), PressureAlpha).ToFColor(true));

    DirectiveLabel->SetText(FText::FromString(GameMode->GetCurrentDirective().ToUpper()));
    DirectiveLabel->SetTextRenderColor(FMath::Lerp(FLinearColor(1.0f, 0.9f, 0.72f), FLinearColor(1.0f, 0.64f, 0.64f), PressureAlpha).ToFColor(true));

    const float FocusPulse = 0.5f + (0.5f * FMath::Sin(AtmospherePhase * 1.6f));
    FocusLight->SetIntensity(1500.0f + (1400.0f * FocusPulse) + (500.0f * PressureAlpha));
    FocusLight->SetLightColor(FMath::Lerp(FLinearColor(0.55f, 0.8f, 1.0f), FLinearColor(1.0f, 0.55f, 0.55f), PressureAlpha).ToFColor(true));

    RoomAudio->SetVolumeMultiplier(0.22f + (0.1f * PressureAlpha));
    RoomAudio->SetPitchMultiplier(0.62f + (0.06f * PressureAlpha));
}
