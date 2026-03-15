#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Glitch459PMOfficeShell.generated.h"

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
    class UTextRenderComponent* RoomLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* ObjectLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* ExitLabel;

    UPROPERTY(VisibleAnywhere)
    class UTextRenderComponent* DirectiveLabel;

    UPROPERTY(VisibleAnywhere)
    class UPointLightComponent* OverheadLight;

    UPROPERTY(VisibleAnywhere)
    class UPointLightComponent* FocusLight;

    UPROPERTY(VisibleAnywhere)
    class UAudioComponent* RoomAudio;

    float AtmospherePhase = 0.0f;

    void ConfigureSurface(class UStaticMeshComponent* MeshComponent, const FVector& RelativeLocation, const FVector& RelativeScale, const FRotator& RelativeRotation = FRotator::ZeroRotator) const;
    void RefreshAtmosphere(float DeltaSeconds);
};
