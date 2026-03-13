#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Glitch459PMHUD.generated.h"

UCLASS()
class GLITCH459PM_API AGlitch459PMHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
