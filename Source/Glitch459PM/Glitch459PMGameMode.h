#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Glitch459PMGameMode.generated.h"

enum class ELoopDirectiveType : uint8
{
    None,
    CompleteTask,
    StabilizeAnomaly,
    ReachRoom,
    InspectObject
};

UENUM()
enum class EGlitchAnomalyClass : uint8
{
    Unknown,
    Temporal,
    Organic,
    Surveillance,
    Spatial,
    Intercom,
    Identity
};

struct FGlitchDiscoveryNote
{
    FName Id;
    FString Label;
    FString Hint;
};

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

    UPROPERTY()
    FName RequiredShortcut;
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

    UPROPERTY()
    EGlitchAnomalyClass AnomalyClass = EGlitchAnomalyClass::Unknown;
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

USTRUCT()
struct FGlitchIntercomLine
{
    GENERATED_BODY()

    UPROPERTY()
    FName VoiceKey;

    UPROPERTY()
    FString Text;
};

UCLASS()
class GLITCH459PM_API AGlitch459PMGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGlitch459PMGameMode();

    virtual void BeginPlay() override;

    FString GetClockText() const;
    int32 GetEffectiveLoopDuration() const;
    int32 GetSecondsRemaining() const;
    int32 GetCurrentLoop() const { return CurrentLoop; }
    int32 GetResolvedAnomalies() const { return ResolvedAnomalies; }
    int32 GetRequiredAnomalies() const { return RequiredAnomalies; }
    bool HasWon() const { return bGameWon; }
    bool HasLost() const { return bGameLost; }
    bool HasEnded() const { return bGameWon || bGameLost; }
    FString GetEndingHeadline() const { return EndingHeadline; }
    FString GetEndingBody() const { return EndingBody; }

    FString GetCurrentRoomName() const;
    FString GetCurrentRoomDescription() const;
    FString GetTerminalStatusText() const;
    FString GetSelectedObjectName() const;
    FString GetSelectedExitLabel() const;
    FString GetSelectedObjectDescriptionAndClue();
    FString GetLastInspectionText() const { return LastInspectionText; }

    FString GetNarrativeStageLabel() const;
    int32 GetPressureLevel() const { return PressureLevel; }
    int32 GetComplianceScore() const { return ComplianceScore; }
    int32 GetDiscoveredShortcutCount() const { return DiscoveredShortcuts.Num(); }
    int32 GetCompletedTaskCount() const { return CompletedTaskCount; }
    int32 GetCollectedFragmentCount() const { return CollectedFragments.Num(); }
    int32 GetRequiredFragmentCount() const { return RequiredFragments; }
    bool IsIntercomActiveThisLoop() const { return bIntercomActiveThisLoop; }
    FString GetCurrentIntercomLine() const { return CurrentIntercomLine; }
    FName GetCurrentIntercomVoiceKey() const { return CurrentIntercomVoiceKey; }
    int32 GetIntercomEventCount() const { return IntercomEventCount; }
    int32 GetReportEventCount() const { return ReportEventCount; }
    bool WasLastReportCorrect() const { return bLastReportCorrect; }
    FName GetLastReportedAnomalyId() const { return LastReportedAnomalyId; }
    FName GetLastReportedRoomId() const { return LastReportedRoomId; }
    EGlitchAnomalyClass GetLastReportedAnomalyClass() const { return LastReportedAnomalyClass; }
    int32 GetMissedAnomalyEventCount() const { return MissedAnomalyEventCount; }
    FName GetLastMissedAnomalyId() const { return LastMissedAnomalyId; }
    FName GetLastMissedRoomId() const { return LastMissedRoomId; }
    EGlitchAnomalyClass GetLastMissedAnomalyClass() const { return LastMissedAnomalyClass; }
    FString GetCurrentPremonition() const { return CurrentPremonition; }
    FString GetCurrentDirective() const { return CurrentDirectiveText; }
    FString GetLastLoopReview() const { return LastLoopReview; }
    FString GetShortcutDossierText() const;
    FString GetFragmentDossierText() const;
    FString GetExitForecastText() const;
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

#if WITH_DEV_AUTOMATION_TESTS
    void AutomationInitializeForTests();
    bool AutomationSetCurrentRoom(FName RoomId);
    bool AutomationSetSelectedObjectById(FName ObjectId);
    bool AutomationSetCurrentAnomalyById(FName AnomalyId);
    void AutomationSetCurrentLoop(int32 LoopNumber);
    void AutomationSetProgressState(int32 NewResolvedAnomalies, int32 NewCompletedTasks, int32 NewComplianceScore);
    bool AutomationForceDiscoverShortcut(FName ShortcutId);
    bool AutomationForceCollectFragment(FName FragmentId);
    FName AutomationGetCurrentRoomId() const { return CurrentRoomId; }
    FName AutomationGetSelectedObjectId() const;
#endif

private:
    void EnsurePlayableSpace();
    void PositionPlayerForPlay() const;
    void TickLoopSecond();
    void ResetLoop();
    void SeedNarrativeData();
    void SeedTaskPools();
    void BuildLoopTasks();
    void ApplyNarrativeBeatForLoop();
    void EvaluateLoopPressure();
    void EvaluateDirectiveOutcome();
    void HandleIntercomWhisper();
    void GenerateDirective();
    void GeneratePremonition();
    void AddLog(const FString& Message);
    void PickNextAnomaly();
    const FGlitchRoom* GetCurrentRoom() const;
    const FGlitchAnomaly* GetCurrentAnomaly() const;
    bool IsSelectedObjectAnomaly() const;
    bool IsExitUnlocked(const FGlitchExit& Exit, FString& OutReason) const;

    const FGlitchTask* GetSelectedTask() const;
    FGlitchTask* GetSelectedTaskMutable();
    bool IsTaskEligibleForCurrentLoop(const FGlitchTask& Task) const;

    bool TryUnlockShortcut(const FName& ShortcutId, const FString& DiscoveryMessage);
    bool TryCollectFragment(const FName& FragmentId, const FString& DiscoveryMessage);
    EGlitchAnomalyClass ResolveAnomalyClass(const FGlitchAnomaly* Anomaly) const;

    FString BuildObjectDisplayName(const FName& ObjectId) const;
    FString BuildRoomDistortionText(const FName& RoomId) const;
    FString BuildDiscoveryLedger(const TArray<FGlitchDiscoveryNote>& Notes, const TSet<FName>& UnlockedSet) const;
    void SeedDiscoveryNotes();

    UPROPERTY()
    TMap<FName, FGlitchRoom> Rooms;

    UPROPERTY()
    TMap<FName, FString> ObjectDescriptions;

    UPROPERTY()
    TArray<FGlitchAnomaly> AnomalyDeck;

    TArray<FGlitchDiscoveryNote> ShortcutNotes;

    TArray<FGlitchDiscoveryNote> FragmentNotes;

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

    UPROPERTY()
    int32 PressureLevel = 0;

    UPROPERTY()
    int32 ComplianceScore = 0;

    UPROPERTY(EditDefaultsOnly)
    int32 RequiredAnomalies = 5;

    UPROPERTY(EditDefaultsOnly)
    int32 LoopDurationSeconds = 180;

    UPROPERTY(EditDefaultsOnly)
    int32 MaxOverloadStrikes = 3;

    UPROPERTY()
    bool bAnomalyFlaggedThisLoop = false;

    UPROPERTY()
    bool bGameWon = false;

    UPROPERTY()
    bool bGameLost = false;

    UPROPERTY()
    bool bEndingHintLogged = false;

    UPROPERTY()
    TArray<FString> LogLines;

    UPROPERTY()
    FString LastInspectionText;

    UPROPERTY()
    int32 OverloadStrikes = 0;

    UPROPERTY()
    FString EndingHeadline;

    UPROPERTY()
    FString EndingBody;

    UPROPERTY()
    TSet<FName> DiscoveredShortcuts;

    UPROPERTY()
    TSet<FName> CollectedFragments;

    UPROPERTY()
    TSet<FName> SeenAnomaliesThisCycle;

    UPROPERTY()
    FName LastMundaneTaskId;

    UPROPERTY()
    FName LastSurrealTaskId;

    UPROPERTY(EditDefaultsOnly)
    int32 RequiredFragments = 3;

    UPROPERTY()
    bool bIntercomActiveThisLoop = false;

    UPROPERTY()
    int32 NextIntercomSecond = 20;

    UPROPERTY()
    int32 LastIntercomLineIndex = INDEX_NONE;

    UPROPERTY()
    FString CurrentIntercomLine;

    UPROPERTY()
    FName CurrentIntercomVoiceKey;

    UPROPERTY()
    int32 IntercomEventCount = 0;

    UPROPERTY()
    int32 ReportEventCount = 0;

    UPROPERTY()
    bool bLastReportCorrect = false;

    UPROPERTY()
    FName LastReportedAnomalyId;

    UPROPERTY()
    FName LastReportedRoomId;

    UPROPERTY()
    EGlitchAnomalyClass LastReportedAnomalyClass = EGlitchAnomalyClass::Unknown;

    UPROPERTY()
    int32 MissedAnomalyEventCount = 0;

    UPROPERTY()
    FName LastMissedAnomalyId;

    UPROPERTY()
    FName LastMissedRoomId;

    UPROPERTY()
    EGlitchAnomalyClass LastMissedAnomalyClass = EGlitchAnomalyClass::Unknown;

    UPROPERTY()
    FString CurrentPremonition;

    ELoopDirectiveType CurrentDirectiveType = ELoopDirectiveType::None;
    FName DirectiveTargetRoom;
    FName DirectiveTargetObject;

    UPROPERTY()
    FString CurrentDirectiveText;

    UPROPERTY()
    bool bDirectiveCompletedThisLoop = false;

    UPROPERTY()
    FString LastLoopReview;

    UPROPERTY()
    TObjectPtr<class AActor> SpawnedOfficeShell;

    UPROPERTY()
    TObjectPtr<class AGlitch459PMStatusTerminal> SpawnedStatusTerminal;

    FTimerHandle LoopTimerHandle;
};
