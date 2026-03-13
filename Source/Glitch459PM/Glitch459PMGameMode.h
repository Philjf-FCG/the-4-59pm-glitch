#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Glitch459PMGameMode.generated.h"

USTRUCT()
struct FGlitchExit
{
    GENERATED_BODY()

    UPROPERTY()
    FName TargetRoom;

    UPROPERTY()
    FString Label;

    UPROPERTY()
    bool bFinalExit = false;

    UPROPERTY()
    int32 RequiredLoop = 1;

    UPROPERTY()
    int32 RequiredCompletedTasks = 0;

    UPROPERTY()
    FString LockedReason;
};

USTRUCT()
struct FGlitchRoom
{
    GENERATED_BODY()

    UPROPERTY()
    FName RoomId;

    UPROPERTY()
    FString DisplayName;

    UPROPERTY()
    FString Description;

    UPROPERTY()
    TArray<FName> Objects;

    UPROPERTY()
    TArray<FGlitchExit> Exits;
};

USTRUCT()
struct FGlitchAnomaly
{
    GENERATED_BODY()

    UPROPERTY()
    FName Id;

    UPROPERTY()
    FName RoomId;

    UPROPERTY()
    FName ObjectId;

    UPROPERTY()
    FString Description;

    UPROPERTY()
    FString Clue;
};

USTRUCT()
struct FGlitchTask
{
    GENERATED_BODY()

    UPROPERTY()
    FName Id;

    UPROPERTY()
    FString Prompt;

    UPROPERTY()
    FName RequiredRoom;

    UPROPERTY()
    FName RequiredObject;

    UPROPERTY()
    bool bSurreal = false;

    UPROPERTY()
    bool bCompleted = false;

    UPROPERTY()
    FString CompletionText;
};

UCLASS()
class GLITCH459PM_API AGlitch459PMGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGlitch459PMGameMode();

    virtual void BeginPlay() override;

    FString GetClockText() const;
    int32 GetCurrentLoop() const { return CurrentLoop; }
    int32 GetResolvedAnomalies() const { return ResolvedAnomalies; }
    int32 GetRequiredAnomalies() const { return RequiredAnomalies; }
    bool HasWon() const { return bGameWon; }

    FString GetCurrentRoomName() const;
    FString GetCurrentRoomDescription() const;
    FString GetSelectedObjectName() const;
    FString GetSelectedExitLabel() const;
    FString GetSelectedObjectDescriptionAndClue();
    FString GetLastInspectionText() const { return LastInspectionText; }

    FString GetNarrativeStageLabel() const;
    int32 GetCompletedTaskCount() const { return CompletedTaskCount; }
    FString GetSelectedTaskPrompt() const;
    bool IsSelectedTaskCompleted() const;

    const TArray<FString>& GetLogLines() const { return LogLines; }

    void SelectNextObject();
    void SelectPreviousObject();
    void SelectNextExit();
    void SelectPreviousExit();
    void SelectNextTask();
    void SelectPreviousTask();

    bool TryFlagSelectedObject();
    bool TryUseSelectedExit();
    bool TryCompleteSelectedTask();

private:
    void TickLoopSecond();
    void ResetLoop();
    void SeedNarrativeData();
    void SeedTaskPools();
    void BuildLoopTasks();
    void ApplyNarrativeBeatForLoop();
    void AddLog(const FString& Message);
    void PickNextAnomaly();
    const FGlitchRoom* GetCurrentRoom() const;
    const FGlitchAnomaly* GetCurrentAnomaly() const;
    bool IsSelectedObjectAnomaly() const;
    bool IsExitUnlocked(const FGlitchExit& Exit, FString& OutReason) const;

    const FGlitchTask* GetSelectedTask() const;
    FGlitchTask* GetSelectedTaskMutable();

    FString BuildObjectDisplayName(const FName& ObjectId) const;

    UPROPERTY()
    TMap<FName, FGlitchRoom> Rooms;

    UPROPERTY()
    TMap<FName, FString> ObjectDescriptions;

    UPROPERTY()
    TArray<FGlitchAnomaly> AnomalyDeck;

    UPROPERTY()
    TArray<FGlitchTask> MundaneTaskPool;

    UPROPERTY()
    TArray<FGlitchTask> SurrealTaskPool;

    UPROPERTY()
    TArray<FGlitchTask> CurrentLoopTasks;

    UPROPERTY()
    FName CurrentRoomId;

    UPROPERTY()
    int32 SelectedObjectIndex = 0;

    UPROPERTY()
    int32 SelectedExitIndex = 0;

    UPROPERTY()
    int32 CurrentAnomalyIndex = INDEX_NONE;

    UPROPERTY()
    int32 SelectedTaskIndex = 0;

    UPROPERTY()
    int32 CurrentLoop = 1;

    UPROPERTY()
    int32 CurrentSecond = 0;

    UPROPERTY()
    int32 ResolvedAnomalies = 0;

    UPROPERTY()
    int32 CompletedTaskCount = 0;

    UPROPERTY(EditDefaultsOnly)
    int32 RequiredAnomalies = 5;

    UPROPERTY(EditDefaultsOnly)
    int32 LoopDurationSeconds = 60;

    UPROPERTY()
    bool bAnomalyFlaggedThisLoop = false;

    UPROPERTY()
    bool bGameWon = false;

    UPROPERTY()
    bool bEndingHintLogged = false;

    UPROPERTY()
    TArray<FString> LogLines;

    UPROPERTY()
    FString LastInspectionText;

    FTimerHandle LoopTimerHandle;
};
