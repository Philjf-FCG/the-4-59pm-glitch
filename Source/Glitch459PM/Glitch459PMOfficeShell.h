#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Glitch459PMOfficeShell.generated.h"

USTRUCT()
struct FGlitchIntercomVoiceAsset
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Audio|VO")
    FName VoiceKey;

    UPROPERTY(EditAnywhere, Category = "Audio|VO")
    TObjectPtr<class USoundBase> Sound;
};

UCLASS()
class GLITCH459PM_API AGlitch459PMOfficeShell : public AActor
{
    GENERATED_BODY()

public:
    AGlitch459PMOfficeShell();

    virtual void Tick(float DeltaSeconds) override;

private:
    UPROPERTY(VisibleAnywhere)
    class USceneComponent* SceneRoot;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Floor;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Ceiling;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* NorthWall;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* SouthWall;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* EastWall;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* WestWall;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Desk;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Door;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* StainPanel;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* StonePlinth;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* RoomLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* ObjectLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* ExitLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* DirectiveLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* TaskLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* PremonitionLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* StatusLabel;

    UPROPERTY(VisibleAnywhere)
    class UPointLightComponent* OverheadLight;

    UPROPERTY(VisibleAnywhere)
    class UPointLightComponent* FocusLight;

    UPROPERTY(VisibleAnywhere)
    class UPointLightComponent* IntercomLight;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* RoomAudio;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* HVACAudio;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* ClockAudio;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* FluorescentAudio;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* IntercomBedAudio;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* IntercomVoiceAudio;

    UPROPERTY(Transient)
    TObjectPtr<class UMaterialInterface> WallMaterialAsset;

    UPROPERTY(Transient)
    TObjectPtr<class UMaterialInterface> CeilingMaterialAsset;

    UPROPERTY(Transient)
    TObjectPtr<class UMaterialInterface> FloorMaterialAsset;

    UPROPERTY(Transient)
    TObjectPtr<class UMaterialInterface> MetalMaterialAsset;

    UPROPERTY(Transient)
    TObjectPtr<class UMaterialInterface> AccentMaterialAsset;

    UPROPERTY(Transient)
    TObjectPtr<class UMaterialInterface> StainMaterialAsset;

    UPROPERTY(Transient)
    TObjectPtr<class UMaterialInterface> StoneMaterialAsset;

    UPROPERTY(Transient)
    TObjectPtr<class USoundBase> IntercomStingerSound;

    UPROPERTY(Transient)
    TObjectPtr<class USoundBase> PressureStingerSound;

    UPROPERTY(EditAnywhere, Category = "Audio|VO")
    TArray<FGlitchIntercomVoiceAsset> IntercomVoiceAssets;

    UPROPERTY(EditAnywhere, Category = "Audio|VO")
    TObjectPtr<class USoundBase> IntercomBuzzLoop;

    UPROPERTY(EditAnywhere, Category = "Audio|VO")
    FString IntercomVoiceAssetRoot = TEXT("/Game/Audio/VO/Intercom");

    UPROPERTY(EditAnywhere, Category = "Audio|Ambience")
    FString HVACLoopAssetPath = TEXT("/Game/Audio/Ambience/A_HVACHum.A_HVACHum");

    UPROPERTY(EditAnywhere, Category = "Audio|Ambience")
    FString ClockLoopAssetPath = TEXT("/Game/Audio/Ambience/A_ClockTick.A_ClockTick");

    UPROPERTY(EditAnywhere, Category = "Audio|Ambience")
    FString FluorescentLoopAssetPath = TEXT("/Game/Audio/Ambience/A_FluorescentBuzz.A_FluorescentBuzz");

    UPROPERTY(Transient)
    TMap<FName, TObjectPtr<class USoundBase>> ResolvedIntercomVoiceCache;

    float AtmospherePhase = 0.0f;
    int32 LastStyledLoop = INDEX_NONE;
    int32 LastAudioPressureLevel = INDEX_NONE;
    int32 LastIntercomEventCount = 0;
    int32 LastReportEventCount = 0;
    int32 LastMissedAnomalyEventCount = 0;
    bool bWasIntercomActive = false;
    float SmoothedIntercomDuck = 1.0f;

    void ConfigureSurface(class UStaticMeshComponent* MeshComponent, const FVector& RelativeLocation, const FVector& RelativeScale, const FRotator& RelativeRotation = FRotator::ZeroRotator) const;
    void ApplyLoopMaterialVariation(int32 LoopNumber, int32 PressureLevel);
    void PlayReactiveStinger(class USoundBase* Sound, const FVector& WorldLocation, float VolumeMultiplier, float PitchMultiplier) const;
    class USoundBase* FindIntercomVoiceAsset(FName VoiceKey) const;
    FString BuildIntercomVoiceAssetPath(FName VoiceKey) const;
    class USoundBase* LoadLoopOrFallback(const FString& AssetPath, class USoundBase* FallbackSound) const;
    void RefreshAtmosphere(float DeltaSeconds);
};
