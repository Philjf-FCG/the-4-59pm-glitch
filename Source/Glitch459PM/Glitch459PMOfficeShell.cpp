#include "Glitch459PMOfficeShell.h"

#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Glitch459PMGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"

AGlitch459PMOfficeShell::AGlitch459PMOfficeShell()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> WallMaterial(TEXT("/Game/Horror/Materials/M_HorrorWall.M_HorrorWall"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> CeilingMaterial(TEXT("/Game/Horror/Materials/M_HorrorCeiling.M_HorrorCeiling"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> FloorMaterial(TEXT("/Game/Horror/Materials/M_HorrorFloor.M_HorrorFloor"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MetalMaterial(TEXT("/Game/Horror/Materials/M_HorrorMetal.M_HorrorMetal"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> AccentMaterial(TEXT("/Game/Horror/Materials/M_HorrorAccent.M_HorrorAccent"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> StainMaterial(TEXT("/Game/Horror/Materials/M_HorrorStain.M_HorrorStain"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> StoneMaterial(TEXT("/Game/Horror/Materials/M_HorrorStone.M_HorrorStone"));
    static ConstructorHelpers::FObjectFinder<USoundBase> AmbientSound(TEXT("/Engine/EditorSounds/Notifications/CompileStart_Cue.CompileStart_Cue"));
    static ConstructorHelpers::FObjectFinder<USoundBase> IntercomStinger(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue.CompileSuccess_Cue"));
    static ConstructorHelpers::FObjectFinder<USoundBase> PressureStinger(TEXT("/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue"));

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

    Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
    Door->SetupAttachment(SceneRoot);

    StainPanel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StainPanel"));
    StainPanel->SetupAttachment(SceneRoot);

    StonePlinth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StonePlinth"));
    StonePlinth->SetupAttachment(SceneRoot);

    RoomLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RoomLabel"));
    RoomLabel->SetupAttachment(SceneRoot);

    ObjectLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ObjectLabel"));
    ObjectLabel->SetupAttachment(SceneRoot);

    ExitLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ExitLabel"));
    ExitLabel->SetupAttachment(SceneRoot);

    DirectiveLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DirectiveLabel"));
    DirectiveLabel->SetupAttachment(SceneRoot);

    TaskLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TaskLabel"));
    TaskLabel->SetupAttachment(SceneRoot);

    PremonitionLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PremonitionLabel"));
    PremonitionLabel->SetupAttachment(SceneRoot);

    StatusLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("StatusLabel"));
    StatusLabel->SetupAttachment(SceneRoot);

    OverheadLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("OverheadLight"));
    OverheadLight->SetupAttachment(SceneRoot);

    FocusLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FocusLight"));
    FocusLight->SetupAttachment(SceneRoot);

    IntercomLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("IntercomLight"));
    IntercomLight->SetupAttachment(SceneRoot);

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

    IntercomBedAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("IntercomBedAudio"));
    IntercomBedAudio->SetupAttachment(SceneRoot);
    IntercomBedAudio->bAutoActivate = false;
    IntercomBedAudio->SetRelativeLocation(FVector(500.0f, -260.0f, 220.0f));
    IntercomBedAudio->SetVolumeMultiplier(0.18f);
    IntercomBedAudio->SetPitchMultiplier(0.92f);
    IntercomBedAudio->bAllowSpatialization = true;
    IntercomBedAudio->bOverrideAttenuation = true;
    IntercomBedAudio->AttenuationOverrides.bAttenuate = true;
    IntercomBedAudio->AttenuationOverrides.bSpatialize = true;
    IntercomBedAudio->AttenuationOverrides.AttenuationShapeExtents = FVector(100.0f, 0.0f, 0.0f);
    IntercomBedAudio->AttenuationOverrides.FalloffDistance = 1600.0f;
    IntercomBedAudio->AttenuationOverrides.dBAttenuationAtMax = -28.0f;

    IntercomVoiceAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("IntercomVoiceAudio"));
    IntercomVoiceAudio->SetupAttachment(SceneRoot);
    IntercomVoiceAudio->bAutoActivate = false;
    IntercomVoiceAudio->SetRelativeLocation(FVector(500.0f, -260.0f, 220.0f));
    IntercomVoiceAudio->SetVolumeMultiplier(0.92f);
    IntercomVoiceAudio->SetPitchMultiplier(1.0f);
    IntercomVoiceAudio->bAllowSpatialization = true;
    IntercomVoiceAudio->bOverrideAttenuation = true;
    IntercomVoiceAudio->AttenuationOverrides.bAttenuate = true;
    IntercomVoiceAudio->AttenuationOverrides.bSpatialize = true;
    IntercomVoiceAudio->AttenuationOverrides.AttenuationShapeExtents = FVector(120.0f, 0.0f, 0.0f);
    IntercomVoiceAudio->AttenuationOverrides.FalloffDistance = 2400.0f;
    IntercomVoiceAudio->AttenuationOverrides.dBAttenuationAtMax = -20.0f;

    if (CubeMesh.Succeeded())
    {
        Floor->SetStaticMesh(CubeMesh.Object);
        Ceiling->SetStaticMesh(CubeMesh.Object);
        NorthWall->SetStaticMesh(CubeMesh.Object);
        SouthWall->SetStaticMesh(CubeMesh.Object);
        EastWall->SetStaticMesh(CubeMesh.Object);
        WestWall->SetStaticMesh(CubeMesh.Object);
        Desk->SetStaticMesh(CubeMesh.Object);
        Door->SetStaticMesh(CubeMesh.Object);
        StainPanel->SetStaticMesh(CubeMesh.Object);
        StonePlinth->SetStaticMesh(CubeMesh.Object);
    }

    if (WallMaterial.Succeeded())
    {
        WallMaterialAsset = WallMaterial.Object;
        NorthWall->SetMaterial(0, WallMaterial.Object);
        SouthWall->SetMaterial(0, WallMaterial.Object);
        EastWall->SetMaterial(0, WallMaterial.Object);
        WestWall->SetMaterial(0, WallMaterial.Object);
    }

    if (CeilingMaterial.Succeeded())
    {
        CeilingMaterialAsset = CeilingMaterial.Object;
        Ceiling->SetMaterial(0, CeilingMaterial.Object);
    }

    if (FloorMaterial.Succeeded())
    {
        FloorMaterialAsset = FloorMaterial.Object;
        Floor->SetMaterial(0, FloorMaterial.Object);
    }

    if (MetalMaterial.Succeeded())
    {
        MetalMaterialAsset = MetalMaterial.Object;
        Desk->SetMaterial(0, MetalMaterial.Object);
    }

    if (AccentMaterial.Succeeded())
    {
        AccentMaterialAsset = AccentMaterial.Object;
        Door->SetMaterial(0, AccentMaterial.Object);
    }

    if (StainMaterial.Succeeded())
    {
        StainMaterialAsset = StainMaterial.Object;
        StainPanel->SetMaterial(0, StainMaterial.Object);
    }

    if (StoneMaterial.Succeeded())
    {
        StoneMaterialAsset = StoneMaterial.Object;
        StonePlinth->SetMaterial(0, StoneMaterial.Object);
    }

    if (AmbientSound.Succeeded())
    {
        RoomAudio->SetSound(AmbientSound.Object);
    }

    if (IntercomStinger.Succeeded())
    {
        IntercomStingerSound = IntercomStinger.Object;
        IntercomBuzzLoop = IntercomStinger.Object;
    }

    if (PressureStinger.Succeeded())
    {
        PressureStingerSound = PressureStinger.Object;
    }

    ConfigureSurface(Floor, FVector(0.0f, 0.0f, -10.0f), FVector(12.0f, 12.0f, 0.2f));
    ConfigureSurface(Ceiling, FVector(0.0f, 0.0f, 420.0f), FVector(12.0f, 12.0f, 0.2f));
    ConfigureSurface(NorthWall, FVector(0.0f, 600.0f, 200.0f), FVector(12.0f, 0.2f, 4.2f));
    ConfigureSurface(SouthWall, FVector(0.0f, -600.0f, 200.0f), FVector(12.0f, 0.2f, 4.2f));
    ConfigureSurface(EastWall, FVector(600.0f, 0.0f, 200.0f), FVector(0.2f, 12.0f, 4.2f));
    ConfigureSurface(WestWall, FVector(-600.0f, 0.0f, 200.0f), FVector(0.2f, 12.0f, 4.2f));
    ConfigureSurface(Desk, FVector(280.0f, 0.0f, 42.0f), FVector(1.8f, 0.9f, 0.5f));
    ConfigureSurface(Door, FVector(0.0f, -588.0f, 150.0f), FVector(1.2f, 0.16f, 3.0f));
    ConfigureSurface(StainPanel, FVector(594.0f, 240.0f, 130.0f), FVector(0.03f, 3.0f, 1.9f), FRotator(0.0f, 0.0f, -4.0f));
    ConfigureSurface(StonePlinth, FVector(-260.0f, 320.0f, 24.0f), FVector(1.15f, 0.9f, 0.26f));

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

    TaskLabel->SetRelativeLocation(FVector(-470.0f, 260.0f, 180.0f));
    TaskLabel->SetRelativeRotation(FRotator(0.0f, 55.0f, 0.0f));
    TaskLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Left);
    TaskLabel->SetText(FText::FromString(TEXT("TASK BOARD")));
    TaskLabel->SetWorldSize(20.0f);
    TaskLabel->SetTextRenderColor(FColor(255, 210, 180));

    PremonitionLabel->SetRelativeLocation(FVector(0.0f, 520.0f, 180.0f));
    PremonitionLabel->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
    PremonitionLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    PremonitionLabel->SetText(FText::FromString(TEXT("PREMONITION")));
    PremonitionLabel->SetWorldSize(20.0f);
    PremonitionLabel->SetTextRenderColor(FColor(205, 190, 255));

    StatusLabel->SetRelativeLocation(FVector(500.0f, -340.0f, 145.0f));
    StatusLabel->SetRelativeRotation(FRotator(0.0f, -120.0f, 0.0f));
    StatusLabel->SetHorizontalAlignment(EHorizTextAligment::EHTA_Left);
    StatusLabel->SetText(FText::FromString(TEXT("STATUS")));
    StatusLabel->SetWorldSize(18.0f);
    StatusLabel->SetTextRenderColor(FColor(255, 210, 170));

    OverheadLight->SetRelativeLocation(FVector(0.0f, 0.0f, 320.0f));
    OverheadLight->SetIntensity(12000.0f);
    OverheadLight->SetLightColor(FColor(255, 244, 214));
    OverheadLight->AttenuationRadius = 2600.0f;

    FocusLight->SetRelativeLocation(FVector(-150.0f, -40.0f, 150.0f));
    FocusLight->SetIntensity(2400.0f);
    FocusLight->SetLightColor(FColor(145, 210, 255));
    FocusLight->AttenuationRadius = 460.0f;
    FocusLight->SetCastShadows(false);

    IntercomLight->SetRelativeLocation(FVector(500.0f, -260.0f, 220.0f));
    IntercomLight->SetIntensity(0.0f);
    IntercomLight->SetLightColor(FColor(255, 80, 80));
    IntercomLight->AttenuationRadius = 320.0f;
    IntercomLight->SetCastShadows(false);

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

void AGlitch459PMOfficeShell::ApplyLoopMaterialVariation(int32 LoopNumber, int32 PressureLevel)
{
    if (LoopNumber <= 0)
    {
        return;
    }

    FRandomStream Random(LoopNumber * 113 + (PressureLevel * 29));

    TArray<UStaticMeshComponent*> WallSurfaces = { NorthWall, SouthWall, EastWall, WestWall };
    for (UStaticMeshComponent* WallSurface : WallSurfaces)
    {
        if (!WallSurface)
        {
            continue;
        }

        UMaterialInterface* ChosenMaterial = WallMaterialAsset.Get();
        const int32 Roll = Random.RandRange(0, 99);
        if (Roll >= 78 && StoneMaterialAsset)
        {
            ChosenMaterial = StoneMaterialAsset.Get();
        }
        else if (Roll >= 52 && StainMaterialAsset)
        {
            ChosenMaterial = StainMaterialAsset.Get();
        }

        if (ChosenMaterial)
        {
            WallSurface->SetMaterial(0, ChosenMaterial);
        }
    }

    if (StainPanel)
    {
        const bool bHeavyStaining = Random.RandRange(0, 99) < (40 + (PressureLevel * 8));
        StainPanel->SetVisibility(bHeavyStaining, true);
        const float Tilt = Random.FRandRange(-7.0f, 7.0f);
        const float HeightJitter = Random.FRandRange(-12.0f, 18.0f);
        ConfigureSurface(StainPanel, FVector(594.0f, 240.0f, 130.0f + HeightJitter), FVector(0.03f, 3.0f, 1.9f), FRotator(0.0f, 0.0f, Tilt));
    }

    if (StonePlinth)
    {
        const bool bStoneDominant = (Random.RandRange(0, 99) < 55) || PressureLevel >= 3;
        StonePlinth->SetMaterial(0, (bStoneDominant && StoneMaterialAsset) ? StoneMaterialAsset.Get() : FloorMaterialAsset.Get());
        const float ShiftX = Random.FRandRange(-40.0f, 55.0f);
        const float ShiftY = Random.FRandRange(-30.0f, 45.0f);
        ConfigureSurface(StonePlinth, FVector(-260.0f + ShiftX, 320.0f + ShiftY, 24.0f), FVector(1.15f, 0.9f, 0.26f));
    }

    if (Desk)
    {
        const bool bDeskCorrupted = Random.RandRange(0, 99) < (22 + (PressureLevel * 9));
        UMaterialInterface* DeskMaterial = bDeskCorrupted && StainMaterialAsset ? StainMaterialAsset.Get() : MetalMaterialAsset.Get();
        if (DeskMaterial)
        {
            Desk->SetMaterial(0, DeskMaterial);
        }
    }

    if (Door)
    {
        const bool bStoneDoor = Random.RandRange(0, 99) < (10 + (PressureLevel * 6));
        UMaterialInterface* DoorMaterial = bStoneDoor && StoneMaterialAsset ? StoneMaterialAsset.Get() : AccentMaterialAsset.Get();
        if (DoorMaterial)
        {
            Door->SetMaterial(0, DoorMaterial);
        }
    }

    LastStyledLoop = LoopNumber;
}

void AGlitch459PMOfficeShell::PlayReactiveStinger(USoundBase* Sound, const FVector& WorldLocation, float VolumeMultiplier, float PitchMultiplier) const
{
    UWorld* World = GetWorld();
    if (!World || !Sound)
    {
        return;
    }

    UGameplayStatics::PlaySoundAtLocation(World, Sound, WorldLocation, VolumeMultiplier, PitchMultiplier);
}

USoundBase* AGlitch459PMOfficeShell::FindIntercomVoiceAsset(FName VoiceKey) const
{
    if (VoiceKey.IsNone())
    {
        return nullptr;
    }

    if (const TObjectPtr<USoundBase>* CachedSound = ResolvedIntercomVoiceCache.Find(VoiceKey))
    {
        return CachedSound->Get();
    }

    for (const FGlitchIntercomVoiceAsset& Entry : IntercomVoiceAssets)
    {
        if (Entry.VoiceKey == VoiceKey && Entry.Sound)
        {
            const_cast<AGlitch459PMOfficeShell*>(this)->ResolvedIntercomVoiceCache.Add(VoiceKey, Entry.Sound);
            return Entry.Sound.Get();
        }
    }

    const FString AssetPath = BuildIntercomVoiceAssetPath(VoiceKey);
    if (!AssetPath.IsEmpty())
    {
        if (USoundBase* AutoLoadedSound = LoadObject<USoundBase>(nullptr, *AssetPath))
        {
            const_cast<AGlitch459PMOfficeShell*>(this)->ResolvedIntercomVoiceCache.Add(VoiceKey, AutoLoadedSound);
            return AutoLoadedSound;
        }
    }

    return nullptr;
}

FString AGlitch459PMOfficeShell::BuildIntercomVoiceAssetPath(FName VoiceKey) const
{
    if (VoiceKey.IsNone() || IntercomVoiceAssetRoot.IsEmpty())
    {
        return FString();
    }

    const FString AssetName = VoiceKey.ToString();
    return FString::Printf(TEXT("%s/%s.%s"), *IntercomVoiceAssetRoot, *AssetName, *AssetName);
}

void AGlitch459PMOfficeShell::RefreshAtmosphere(float DeltaSeconds)
{
    UWorld* World = GetWorld();
    AGlitch459PMGameMode* GameMode = World ? Cast<AGlitch459PMGameMode>(World->GetAuthGameMode()) : nullptr;
    if (!GameMode)
    {
        return;
    }

    if (LastStyledLoop != GameMode->GetCurrentLoop())
    {
        ApplyLoopMaterialVariation(GameMode->GetCurrentLoop(), GameMode->GetPressureLevel());
    }

    const int32 CurrentPressure = GameMode->GetPressureLevel();
    const bool bIntercomActive = GameMode->IsIntercomActiveThisLoop();
    const int32 CurrentIntercomEventCount = GameMode->GetIntercomEventCount();

    if (bIntercomActive && !bWasIntercomActive)
    {
        PlayReactiveStinger(IntercomStingerSound.Get(), IntercomLight->GetComponentLocation(), 0.42f, 0.92f + (0.04f * CurrentPressure));
    }

    if (CurrentIntercomEventCount > LastIntercomEventCount)
    {
        if (IntercomBuzzLoop)
        {
            IntercomBedAudio->SetSound(IntercomBuzzLoop);
            IntercomBedAudio->Play();
        }

        if (USoundBase* VoiceAsset = FindIntercomVoiceAsset(GameMode->GetCurrentIntercomVoiceKey()))
        {
            IntercomVoiceAudio->SetSound(VoiceAsset);
            IntercomVoiceAudio->Play();
        }
    }

    if (!bIntercomActive)
    {
        IntercomBedAudio->Stop();
    }

    if (LastAudioPressureLevel != INDEX_NONE && CurrentPressure > LastAudioPressureLevel)
    {
        const float PressureStep = static_cast<float>(CurrentPressure - LastAudioPressureLevel);
        PlayReactiveStinger(PressureStingerSound.Get(), OverheadLight->GetComponentLocation(), 0.35f + (0.08f * PressureStep), 0.74f - (0.03f * static_cast<float>(CurrentPressure)));
    }

    bWasIntercomActive = bIntercomActive;
    LastAudioPressureLevel = CurrentPressure;
    LastIntercomEventCount = CurrentIntercomEventCount;

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

    TaskLabel->SetText(FText::FromString(FString::Printf(TEXT("TASK BOARD\n%s"), *GameMode->GetSelectedTaskPrompt().ToUpper())));
    TaskLabel->SetTextRenderColor(FMath::Lerp(FLinearColor(1.0f, 0.84f, 0.72f), FLinearColor(1.0f, 0.66f, 0.66f), PressureAlpha).ToFColor(true));

    PremonitionLabel->SetText(FText::FromString(GameMode->GetCurrentPremonition().ToUpper()));
    PremonitionLabel->SetTextRenderColor(FMath::Lerp(FLinearColor(0.84f, 0.78f, 1.0f), FLinearColor(1.0f, 0.62f, 0.72f), PressureAlpha).ToFColor(true));

    const bool bTaskDone = GameMode->IsSelectedTaskCompleted();
    const float TaskPulse = 0.5f + (0.5f * FMath::Sin(AtmospherePhase * 2.6f));
    const FLinearColor PendingTaskColor = FMath::Lerp(FLinearColor(1.0f, 0.86f, 0.72f), FLinearColor(1.0f, 0.72f, 0.72f), TaskPulse * 0.45f);
    TaskLabel->SetTextRenderColor((bTaskDone ? FLinearColor(0.7f, 1.0f, 0.76f) : PendingTaskColor).ToFColor(true));

    const float IntercomPulse = 0.5f + (0.5f * FMath::Sin(AtmospherePhase * 4.2f));
    IntercomLight->SetIntensity(bIntercomActive ? (900.0f + (2000.0f * IntercomPulse)) : (120.0f + (260.0f * PressureAlpha)));
    IntercomLight->SetLightColor((bIntercomActive
        ? FLinearColor(1.0f, 0.32f, 0.32f)
        : FMath::Lerp(FLinearColor(0.35f, 0.45f, 0.55f), FLinearColor(0.72f, 0.32f, 0.32f), PressureAlpha)).ToFColor(true));

    const FString StatusText = FString::Printf(
        TEXT("STATUS\nINTERCOM %s\nVOICE %s\nTASK %s\n%s"),
        bIntercomActive ? TEXT("ACTIVE") : TEXT("QUIET"),
        GameMode->GetCurrentIntercomVoiceKey().IsNone() ? TEXT("UNASSIGNED") : *GameMode->GetCurrentIntercomVoiceKey().ToString().ToUpper(),
        bTaskDone ? TEXT("DONE") : TEXT("PENDING"),
        *GameMode->GetLastLoopReview().ToUpper()
    );
    StatusLabel->SetText(FText::FromString(StatusText));
    StatusLabel->SetTextRenderColor(FMath::Lerp(FLinearColor(0.95f, 0.84f, 0.72f), FLinearColor(1.0f, 0.62f, 0.62f), PressureAlpha).ToFColor(true));

    const float FocusPulse = 0.5f + (0.5f * FMath::Sin(AtmospherePhase * 1.6f));
    FocusLight->SetIntensity(1500.0f + (1400.0f * FocusPulse) + (500.0f * PressureAlpha));
    FocusLight->SetLightColor(FMath::Lerp(FLinearColor(0.55f, 0.8f, 1.0f), FLinearColor(1.0f, 0.55f, 0.55f), PressureAlpha).ToFColor(true));

    RoomAudio->SetVolumeMultiplier(0.22f + (0.1f * PressureAlpha));
    RoomAudio->SetPitchMultiplier(0.62f + (0.06f * PressureAlpha));
    IntercomBedAudio->SetVolumeMultiplier(0.12f + (0.05f * PressureAlpha));
}
