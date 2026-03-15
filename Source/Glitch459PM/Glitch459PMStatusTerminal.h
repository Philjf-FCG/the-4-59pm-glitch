#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Glitch459PMStatusTerminal.generated.h"

UCLASS()
class GLITCH459PM_API AGlitch459PMStatusTerminal : public AActor
{
    GENERATED_BODY()

public:
    AGlitch459PMStatusTerminal();

    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    class USceneComponent* SceneRoot;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* TerminalPedestal;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* TerminalBody;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* TerminalScreen;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* TerminalKeyboard;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* ScreenText;

    UPROPERTY(VisibleAnywhere)
    class UPointLightComponent* ScreenGlow;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* TerminalAudio;

    UPROPERTY(EditAnywhere, Category = "Terminal")
    float RefreshInterval = 0.25f;

    UPROPERTY(EditAnywhere, Category = "Terminal")
    FString FallbackText = TEXT("TERMINAL OFFLINE");

    UPROPERTY(EditAnywhere, Category = "Terminal")
    float FlickerSpeed = 3.5f;

    UPROPERTY(EditAnywhere, Category = "Terminal")
    float BaseGlowIntensity = 900.0f;

    UPROPERTY(EditAnywhere, Category = "Terminal")
    float FlickerIntensityRange = 260.0f;

    float TimeSinceRefresh = 0.0f;
    float FlickerPhase = 0.0f;

    void RefreshScreen();
};
