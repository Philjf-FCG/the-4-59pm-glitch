#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR

#include "Glitch459PMGameMode.h"
#include "Glitch459PMPawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/InputSettings.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

namespace
{
    constexpr EAutomationTestFlags TestFlags = EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter;

    UWorld* CreateAutomationWorld(FAutomationTestBase& Test)
    {
        UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
        Test.TestNotNull(TEXT("Automation world should exist"), World);
        return World;
    }

    AGlitch459PMGameMode* SpawnInitializedGameMode(UWorld* World, FAutomationTestBase& Test)
    {
        Test.TestNotNull(TEXT("World must exist for game mode spawn"), World);
        if (!World)
        {
            return nullptr;
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AGlitch459PMGameMode* GameMode = World->SpawnActor<AGlitch459PMGameMode>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
        Test.TestNotNull(TEXT("Game mode should spawn"), GameMode);
        if (!GameMode)
        {
            return nullptr;
        }

        GameMode->AutomationInitializeForTests();
        return GameMode;
    }
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGlitchMovementAndSprintTest, "Project.Glitch459PM.Smoke.MovementAndSprint", TestFlags)

bool FGlitchMovementAndSprintTest::RunTest(const FString& Parameters)
{
    UWorld* World = CreateAutomationWorld(*this);
    if (!World)
    {
        return false;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AGlitch459PMPawn* Pawn = World->SpawnActor<AGlitch459PMPawn>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    const UInputSettings* InputSettings = GetDefault<UInputSettings>();

    TestNotNull(TEXT("Pawn should spawn"), Pawn);
    TestNotNull(TEXT("Input settings should exist"), InputSettings);
    if (!Pawn || !InputSettings)
    {
        return false;
    }

    const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();
    const auto HasAxisMapping = [&AxisMappings](const FName AxisName, const FKey& Key, const float Scale)
    {
        for (const FInputAxisKeyMapping& Mapping : AxisMappings)
        {
            if (Mapping.AxisName == AxisName && Mapping.Key == Key && FMath::IsNearlyEqual(Mapping.Scale, Scale))
            {
                return true;
            }
        }

        return false;
    };

    TestTrue(TEXT("MoveForward should map to W"), HasAxisMapping(TEXT("MoveForward"), EKeys::W, 1.0f));
    TestTrue(TEXT("MoveForward should map to S"), HasAxisMapping(TEXT("MoveForward"), EKeys::S, -1.0f));
    TestTrue(TEXT("MoveForward should map to Gamepad_LeftY"), HasAxisMapping(TEXT("MoveForward"), EKeys::Gamepad_LeftY, 1.0f));
    TestTrue(TEXT("MoveRight should map to D"), HasAxisMapping(TEXT("MoveRight"), EKeys::D, 1.0f));
    TestTrue(TEXT("MoveRight should map to A"), HasAxisMapping(TEXT("MoveRight"), EKeys::A, -1.0f));
    TestTrue(TEXT("MoveRight should map to Gamepad_LeftX"), HasAxisMapping(TEXT("MoveRight"), EKeys::Gamepad_LeftX, 1.0f));

    Pawn->AutomationStartSprint();
    TestTrue(TEXT("Sprint should raise speed"), FMath::IsNearlyEqual(Pawn->AutomationGetMaxWalkSpeed(), 450.0f));

    Pawn->AutomationStopSprint();
    TestTrue(TEXT("Stopping sprint should restore walk speed"), FMath::IsNearlyEqual(Pawn->AutomationGetMaxWalkSpeed(), 250.0f));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGlitchObjectSelectionWrapTest, "Project.Glitch459PM.Smoke.ObjectSelectionWraps", TestFlags)

bool FGlitchObjectSelectionWrapTest::RunTest(const FString& Parameters)
{
    UWorld* World = CreateAutomationWorld(*this);
    AGlitch459PMGameMode* GameMode = SpawnInitializedGameMode(World, *this);
    if (!GameMode)
    {
        return false;
    }

    TestTrue(TEXT("Breakroom should be available"), GameMode->AutomationSetCurrentRoom(TEXT("breakroom")));
    TestEqual(TEXT("Initial selected object should be water_cooler"), GameMode->AutomationGetSelectedObjectId(), FName(TEXT("water_cooler")));

    GameMode->SelectPreviousObject();
    TestEqual(TEXT("Selection should wrap to the last breakroom object"), GameMode->AutomationGetSelectedObjectId(), FName(TEXT("breakroom_door")));

    GameMode->SelectNextObject();
    TestEqual(TEXT("Selection should wrap back to the first breakroom object"), GameMode->AutomationGetSelectedObjectId(), FName(TEXT("water_cooler")));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGlitchCorrectAnomalyReportTest, "Project.Glitch459PM.Gameplay.CorrectAnomalyReport", TestFlags)

bool FGlitchCorrectAnomalyReportTest::RunTest(const FString& Parameters)
{
    UWorld* World = CreateAutomationWorld(*this);
    AGlitch459PMGameMode* GameMode = SpawnInitializedGameMode(World, *this);
    if (!GameMode)
    {
        return false;
    }

    TestTrue(TEXT("Breakroom should be available"), GameMode->AutomationSetCurrentRoom(TEXT("breakroom")));
    TestTrue(TEXT("Microwave should be selectable"), GameMode->AutomationSetSelectedObjectById(TEXT("microwave")));
    TestTrue(TEXT("Known anomaly should be selectable"), GameMode->AutomationSetCurrentAnomalyById(TEXT("ink_coffee")));

    const int32 ResolvedBefore = GameMode->GetResolvedAnomalies();
    TestTrue(TEXT("Correct anomaly report should succeed"), GameMode->TryFlagSelectedObject());
    TestEqual(TEXT("Resolved anomaly count should increase"), GameMode->GetResolvedAnomalies(), ResolvedBefore + 1);
    TestEqual(TEXT("Correct report should not raise pressure at baseline"), GameMode->GetPressureLevel(), 0);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGlitchFalseAnomalyReportTest, "Project.Glitch459PM.Gameplay.FalseAnomalyReport", TestFlags)

bool FGlitchFalseAnomalyReportTest::RunTest(const FString& Parameters)
{
    UWorld* World = CreateAutomationWorld(*this);
    AGlitch459PMGameMode* GameMode = SpawnInitializedGameMode(World, *this);
    if (!GameMode)
    {
        return false;
    }

    TestTrue(TEXT("Breakroom should be available"), GameMode->AutomationSetCurrentRoom(TEXT("breakroom")));
    TestTrue(TEXT("Water cooler should be selectable"), GameMode->AutomationSetSelectedObjectById(TEXT("water_cooler")));
    TestTrue(TEXT("Known anomaly should be selectable"), GameMode->AutomationSetCurrentAnomalyById(TEXT("ink_coffee")));

    TestFalse(TEXT("Incorrect anomaly report should fail"), GameMode->TryFlagSelectedObject());
    TestEqual(TEXT("False report should raise pressure by one"), GameMode->GetPressureLevel(), 1);
    return true;
}

#endif