#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Glitch459PMPlayerController.generated.h"

UCLASS()
class GLITCH459PM_API AGlitch459PMPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    class AGlitch459PMGameMode* GetGlitchGameMode() const;

    void OnNextObject();
    void OnPrevObject();
    void OnNextExit();
    void OnPrevExit();
    void OnNextTask();
    void OnPrevTask();
    void OnInspect();
    void OnFlagAnomaly();
    void OnCompleteTask();
    void OnUseExit();
};
