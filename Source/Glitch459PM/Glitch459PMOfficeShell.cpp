#include "Glitch459PMOfficeShell.h"

#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "UObject/ConstructorHelpers.h"

AGlitch459PMOfficeShell::AGlitch459PMOfficeShell()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));

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

    OverheadLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("OverheadLight"));
    OverheadLight->SetupAttachment(SceneRoot);

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

    OverheadLight->SetRelativeLocation(FVector(0.0f, 0.0f, 320.0f));
    OverheadLight->SetIntensity(12000.0f);
    OverheadLight->SetLightColor(FColor(255, 244, 214));
    OverheadLight->AttenuationRadius = 2600.0f;
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
