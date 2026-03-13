#include "Glitch459PMGameMode.h"

#include "Glitch459PMHUD.h"
#include "Glitch459PMPawn.h"
#include "Glitch459PMPlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"

AGlitch459PMGameMode::AGlitch459PMGameMode()
{
    PlayerControllerClass = AGlitch459PMPlayerController::StaticClass();
    DefaultPawnClass = AGlitch459PMPawn::StaticClass();
    HUDClass = AGlitch459PMHUD::StaticClass();
}

void AGlitch459PMGameMode::BeginPlay()
{
    Super::BeginPlay();

    SeedNarrativeData();
    SeedTaskPools();

    CurrentRoomId = TEXT("breakroom");
    LastInspectionText = TEXT("Friday, 4:59 PM. Your badge still works. For now.");

    PickNextAnomaly();
    BuildLoopTasks();

    AddLog(TEXT("Arthur, final reminder: finish the Final Friday Report before 5:00 PM to secure your promotion."));

    GetWorldTimerManager().SetTimer(
        LoopTimerHandle,
        this,
        &AGlitch459PMGameMode::TickLoopSecond,
        1.0f,
        true
    );
}

void AGlitch459PMGameMode::SeedNarrativeData()
{
    Rooms.Empty();
    ObjectDescriptions.Empty();
    AnomalyDeck.Empty();

    {
        FGlitchRoom Room;
        Room.RoomId = TEXT("breakroom");
        Room.DisplayName = TEXT("Breakroom");
        Room.Description = TEXT("Fluorescent lights buzz overhead. Burnt coffee and printer toner hang in the air.");
        Room.Objects = { TEXT("water_cooler"), TEXT("microwave"), TEXT("breakroom_door") };
        Room.Exits = {
            { TEXT("hallway"), TEXT("Step into hallway"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("lobby"), TEXT("Head to lobby"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("server_room"), TEXT("Use service ladder shortcut"), false, 1, 0, TEXT("A vent panel is bolted shut near the sink."), TEXT("shortcut_service_ladder") }
        };
        Rooms.Add(Room.RoomId, Room);
    }

    {
        FGlitchRoom Room;
        Room.RoomId = TEXT("hallway");
        Room.DisplayName = TEXT("Hallway");
        Room.Description = TEXT("The corridor stretches with sterile symmetry. Framed slogans watch you pass.");
        Room.Objects = { TEXT("wall_clock"), TEXT("poster"), TEXT("exit_sign") };
        Room.Exits = {
            { TEXT("breakroom"), TEXT("Return to breakroom"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("cubicles"), TEXT("Enter cubicles"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("lobby"), TEXT("Walk to lobby"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("server_room"), TEXT("Swipe into server room"), false, 4, 2, TEXT("Access denied. Productivity score too low."), TEXT("") },
            { TEXT("ceo_office"), TEXT("Take executive elevator"), false, 7, 4, TEXT("Executive floor restricted to promoted staff."), TEXT("") }
        };
        Rooms.Add(Room.RoomId, Room);
    }

    {
        FGlitchRoom Room;
        Room.RoomId = TEXT("cubicles");
        Room.DisplayName = TEXT("Cubicle Farm");
        Room.Description = TEXT("Rows of gray partitions. Dozens of monitors glow with unfinished slides.");
        Room.Objects = { TEXT("coworkers"), TEXT("printer"), TEXT("arthur_terminal"), TEXT("desk_photo") };
        Room.Exits = {
            { TEXT("hallway"), TEXT("Back to hallway"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("archive"), TEXT("Crawl through records chute"), false, 1, 0, TEXT("The filing chute is sealed behind your cubicle wall."), TEXT("shortcut_archive_chute") }
        };
        Rooms.Add(Room.RoomId, Room);
    }

    {
        FGlitchRoom Room;
        Room.RoomId = TEXT("lobby");
        Room.DisplayName = TEXT("Lobby");
        Room.Description = TEXT("Glass doors frame a sunset that never changes. The carpet smells damp.");
        Room.Objects = { TEXT("exit_doors"), TEXT("reception_bell"), TEXT("security_camera") };
        Room.Exits = {
            { TEXT("breakroom"), TEXT("Back to breakroom"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("lobby_exit"), TEXT("Go through exit doors"), true, 1, 0, TEXT(""), TEXT("") },
            { TEXT("ceo_office"), TEXT("Use executive fire stair"), false, 1, 0, TEXT("The stairwell keycard reader rejects you."), TEXT("shortcut_fire_stair") }
        };
        Rooms.Add(Room.RoomId, Room);
    }

    {
        FGlitchRoom Room;
        Room.RoomId = TEXT("server_room");
        Room.DisplayName = TEXT("Server Room");
        Room.Description = TEXT("Cold air and white noise. Towers blink like rows of patient eyes.");
        Room.Objects = { TEXT("rack_13"), TEXT("backup_tapes"), TEXT("timecard_terminal") };
        Room.Exits = {
            { TEXT("hallway"), TEXT("Return to hallway"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("archive"), TEXT("Descend to sublevel archive"), false, 10, 7, TEXT("Sublevel lift offline pending managerial approval."), TEXT("") }
        };
        Rooms.Add(Room.RoomId, Room);
    }

    {
        FGlitchRoom Room;
        Room.RoomId = TEXT("ceo_office");
        Room.DisplayName = TEXT("CEO Office");
        Room.Description = TEXT("Polished stone, silent glass, and a skyline that seems painted on.");
        Room.Objects = { TEXT("sealed_envelope"), TEXT("intercom"), TEXT("mirror_wall") };
        Room.Exits = {
            { TEXT("hallway"), TEXT("Return to hallway"), false, 1, 0, TEXT(""), TEXT("") }
        };
        Rooms.Add(Room.RoomId, Room);
    }

    {
        FGlitchRoom Room;
        Room.RoomId = TEXT("archive");
        Room.DisplayName = TEXT("The Archive");
        Room.Description = TEXT("A subterranean floor filled with filing cabinets and exhausted versions of you.");
        Room.Objects = { TEXT("clone_rows"), TEXT("rejected_badges"), TEXT("quit_box") };
        Room.Exits = {
            { TEXT("server_room"), TEXT("Retreat to server room"), false, 1, 0, TEXT(""), TEXT("") },
            { TEXT("lobby"), TEXT("Emergency stair to lobby"), false, 1, 0, TEXT(""), TEXT("") }
        };
        Rooms.Add(Room.RoomId, Room);
    }

    ObjectDescriptions.Add(TEXT("water_cooler"), TEXT("A cheap jug machine humming like a sleeping appliance."));
    ObjectDescriptions.Add(TEXT("microwave"), TEXT("The display blinks 4:59 and pretends it never changed."));
    ObjectDescriptions.Add(TEXT("breakroom_door"), TEXT("The door leaks music like a distant happy hour."));
    ObjectDescriptions.Add(TEXT("wall_clock"), TEXT("Second hand climbing toward 12 with managerial confidence."));
    ObjectDescriptions.Add(TEXT("poster"), TEXT("TEAMWORK: because progress is mandatory."));
    ObjectDescriptions.Add(TEXT("exit_sign"), TEXT("Arrow toggles left then right when you blink."));
    ObjectDescriptions.Add(TEXT("coworkers"), TEXT("They loop the same joke and laugh on the wrong beat."));
    ObjectDescriptions.Add(TEXT("printer"), TEXT("Feeds paper with the patience of a predator."));
    ObjectDescriptions.Add(TEXT("arthur_terminal"), TEXT("Your terminal displays Final Friday Report v187."));
    ObjectDescriptions.Add(TEXT("desk_photo"), TEXT("A framed photo of your coworker's dog. Wait. That's you sleeping here."));
    ObjectDescriptions.Add(TEXT("exit_doors"), TEXT("Automatic doors with a reflection that is one second behind."));
    ObjectDescriptions.Add(TEXT("reception_bell"), TEXT("It rings on its own when the second hand nears 12."));
    ObjectDescriptions.Add(TEXT("security_camera"), TEXT("The red light pulses exactly with your heartbeat."));
    ObjectDescriptions.Add(TEXT("rack_13"), TEXT("Drive activity spikes whenever you think about resigning."));
    ObjectDescriptions.Add(TEXT("backup_tapes"), TEXT("Labeled FRIDAY_REPORT_1976 through FRIDAY_REPORT_2085."));
    ObjectDescriptions.Add(TEXT("timecard_terminal"), TEXT("The scanner displays ARTHUR CLOCKED IN: 12,447 CONSECUTIVE DAYS."));
    ObjectDescriptions.Add(TEXT("sealed_envelope"), TEXT("Envelope marked PROMOTION LETTER. It is always empty."));
    ObjectDescriptions.Add(TEXT("intercom"), TEXT("A voice says your private fears in your own tone."));
    ObjectDescriptions.Add(TEXT("mirror_wall"), TEXT("The reflection waits to mimic you."));
    ObjectDescriptions.Add(TEXT("clone_rows"), TEXT("Rows of Arthurs filing reports that never end."));
    ObjectDescriptions.Add(TEXT("rejected_badges"), TEXT("Thousands of badges stamped INELIGIBLE FOR WEEKEND."));
    ObjectDescriptions.Add(TEXT("quit_box"), TEXT("A suggestion box overflowing with unsigned resignation letters."));

    AnomalyDeck = {
        { TEXT("tentacle_cooler"), TEXT("breakroom"), TEXT("water_cooler"), TEXT("Rubbery tendrils churn inside the jug."), TEXT("The cooler's shadow has too many joints.") },
        { TEXT("ink_coffee"), TEXT("breakroom"), TEXT("microwave"), TEXT("The coffee in your mug ripples black like printer ink."), TEXT("It smells like toner, not coffee.") },
        { TEXT("happy_hour_mirage"), TEXT("breakroom"), TEXT("breakroom_door"), TEXT("Music swells behind the door; beyond it is only abyss."), TEXT("The party has no people, only echo.") },
        { TEXT("screaming_coworkers"), TEXT("cubicles"), TEXT("coworkers"), TEXT("Their banal joke stretches into a continuous scream."), TEXT("Laughter has become a siren.") },
        { TEXT("eternal_todo"), TEXT("cubicles"), TEXT("printer"), TEXT("The printer outputs your life history in reverse order."), TEXT("The paper starts with your retirement and ends at birth.") },
        { TEXT("year_2085"), TEXT("cubicles"), TEXT("arthur_terminal"), TEXT("Unread emails dated 2085 ask for the same report."), TEXT("The sender is still your boss.") },
        { TEXT("breathing_clock"), TEXT("hallway"), TEXT("wall_clock"), TEXT("The clock face fogs in and out with your breath."), TEXT("The ticking now inhales.") },
        { TEXT("bleeding_poster"), TEXT("hallway"), TEXT("poster"), TEXT("TEAMWORK drips downward like wet paint and old blood."), TEXT("A slogan is leaking.") },
        { TEXT("doubled_door"), TEXT("lobby"), TEXT("exit_doors"), TEXT("The glass reflects the breakroom from an impossible angle."), TEXT("Outside has been replaced with inside.") },
        { TEXT("camera_eyelid"), TEXT("lobby"), TEXT("security_camera"), TEXT("The camera blinks. Not a light. An eyelid."), TEXT("Something is watching back.") },
        { TEXT("boss_shoes"), TEXT("ceo_office"), TEXT("intercom"), TEXT("Polished shoes stand beneath the bathroom stall in your reflection."), TEXT("The boss is always just out of frame.") },
        { TEXT("archive_whisper"), TEXT("archive"), TEXT("clone_rows"), TEXT("The clones whisper your employee number in unison."), TEXT("They all clocked out. None left.") }
    };
}

void AGlitch459PMGameMode::SeedTaskPools()
{
    MundaneTaskPool = {
        { TEXT("task_budget"), TEXT("Finalize budget variance notes."), TEXT("cubicles"), TEXT("arthur_terminal"), false, false, TEXT("Budget notes submitted. Another spreadsheet sighs in relief.") },
        { TEXT("task_reconcile"), TEXT("Reconcile Q4 expense entries."), TEXT("cubicles"), TEXT("arthur_terminal"), false, false, TEXT("Expense entries reconciled. Nothing feels resolved.") },
        { TEXT("task_attendance"), TEXT("Validate attendance export in server logs."), TEXT("server_room"), TEXT("timecard_terminal"), false, false, TEXT("Attendance verified. Nobody appears to have gone home.") },
        { TEXT("task_exec_packet"), TEXT("Prepare executive packet in CEO office."), TEXT("ceo_office"), TEXT("sealed_envelope"), false, false, TEXT("Executive packet delivered to an empty desk.") }
    };

    SurrealTaskPool = {
        { TEXT("task_screams"), TEXT("Categorize the screams of accounting by urgency."), TEXT("cubicles"), TEXT("coworkers"), true, false, TEXT("Screams categorized: polite panic, fiscal terror, resignation baritone.") },
        { TEXT("task_reverse"), TEXT("Sort your life events in reverse chronological order."), TEXT("cubicles"), TEXT("printer"), true, false, TEXT("Life sorted backward. The beginning now feels like a deadline.") },
        { TEXT("task_boss"), TEXT("Acknowledge intercom confession and continue working."), TEXT("ceo_office"), TEXT("intercom"), true, false, TEXT("Acknowledgement logged. The voice sounds grateful.") },
        { TEXT("task_archive"), TEXT("File this loop in the Archive under 'Almost Weekend'."), TEXT("archive"), TEXT("quit_box"), true, false, TEXT("Loop filed. Cabinet count increases by one.") }
    };
}

void AGlitch459PMGameMode::BuildLoopTasks()
{
    CurrentLoopTasks.Empty();
    SelectedTaskIndex = 0;

    if (MundaneTaskPool.IsEmpty() || SurrealTaskPool.IsEmpty())
    {
        return;
    }

    const int32 MundaneIndex = FMath::RandRange(0, MundaneTaskPool.Num() - 1);
    FGlitchTask Mundane = MundaneTaskPool[MundaneIndex];
    Mundane.bCompleted = false;
    CurrentLoopTasks.Add(Mundane);

    if (CurrentLoop >= 6)
    {
        const int32 SurrealIndex = FMath::RandRange(0, SurrealTaskPool.Num() - 1);
        FGlitchTask Surreal = SurrealTaskPool[SurrealIndex];
        Surreal.bCompleted = false;
        CurrentLoopTasks.Add(Surreal);
    }

    AddLog(TEXT("Task board refreshed. The report still waits."));
}

void AGlitch459PMGameMode::ApplyNarrativeBeatForLoop()
{
    if (CurrentLoop == 2)
    {
        AddLog(TEXT("Coffee tastes faintly like ink. You tell yourself it's the machine."));
    }
    else if (CurrentLoop == 4)
    {
        AddLog(TEXT("A coworker's desk photo now shows you asleep at your station."));
    }
    else if (CurrentLoop == 7)
    {
        AddLog(TEXT("The office seems larger than before. Hallways multiply when unobserved."));
    }
    else if (CurrentLoop == 10)
    {
        AddLog(TEXT("Unread email flood: 2085. Subject line: Final Friday Report (Urgent)."));
    }
    else if (CurrentLoop == 12)
    {
        AddLog(TEXT("You find the Archive map. The basement was never on the building plan."));
    }
    else if (CurrentLoop == 14)
    {
        AddLog(TEXT("Truth: every Arthur who quit remained employed by the building."));
    }
}

void AGlitch459PMGameMode::EvaluateLoopPressure()
{
    int32 CompletedThisLoop = 0;
    for (const FGlitchTask& Task : CurrentLoopTasks)
    {
        if (Task.bCompleted)
        {
            ++CompletedThisLoop;
        }
    }

    if (!bAnomalyFlaggedThisLoop && CompletedThisLoop == 0)
    {
        PressureLevel = FMath::Min(PressureLevel + 1, 5);
        AddLog(TEXT("You did nothing useful before reset. The office notices."));
        return;
    }

    if (bAnomalyFlaggedThisLoop && CompletedThisLoop > 0)
    {
        PressureLevel = FMath::Max(PressureLevel - 1, 0);
    }
}

void AGlitch459PMGameMode::AddLog(const FString& Message)
{
    LogLines.Insert(Message, 0);
    constexpr int32 MaxLines = 12;
    if (LogLines.Num() > MaxLines)
    {
        LogLines.SetNum(MaxLines);
    }
}

void AGlitch459PMGameMode::PickNextAnomaly()
{
    if (AnomalyDeck.IsEmpty())
    {
        CurrentAnomalyIndex = INDEX_NONE;
        return;
    }

    const int32 LastIndex = CurrentAnomalyIndex;
    int32 NewIndex = FMath::RandRange(0, AnomalyDeck.Num() - 1);

    if (AnomalyDeck.Num() > 1)
    {
        while (NewIndex == LastIndex)
        {
            NewIndex = FMath::RandRange(0, AnomalyDeck.Num() - 1);
        }
    }

    CurrentAnomalyIndex = NewIndex;
}

const FGlitchRoom* AGlitch459PMGameMode::GetCurrentRoom() const
{
    return Rooms.Find(CurrentRoomId);
}

const FGlitchAnomaly* AGlitch459PMGameMode::GetCurrentAnomaly() const
{
    return AnomalyDeck.IsValidIndex(CurrentAnomalyIndex) ? &AnomalyDeck[CurrentAnomalyIndex] : nullptr;
}

bool AGlitch459PMGameMode::IsSelectedObjectAnomaly() const
{
    const FGlitchRoom* Room = GetCurrentRoom();
    const FGlitchAnomaly* Anomaly = GetCurrentAnomaly();

    if (!Room || !Anomaly || !Room->Objects.IsValidIndex(SelectedObjectIndex))
    {
        return false;
    }

    return Anomaly->RoomId == CurrentRoomId && Anomaly->ObjectId == Room->Objects[SelectedObjectIndex];
}

bool AGlitch459PMGameMode::IsExitUnlocked(const FGlitchExit& Exit, FString& OutReason) const
{
    if (!Exit.RequiredShortcut.IsNone() && !DiscoveredShortcuts.Contains(Exit.RequiredShortcut))
    {
        OutReason = TEXT("Shortcut not discovered.");
        return false;
    }

    if (CurrentLoop < Exit.RequiredLoop)
    {
        OutReason = FString::Printf(TEXT("Requires loop %d."), Exit.RequiredLoop);
        return false;
    }

    if (CompletedTaskCount < Exit.RequiredCompletedTasks)
    {
        OutReason = FString::Printf(TEXT("Requires %d completed tasks."), Exit.RequiredCompletedTasks);
        return false;
    }

    OutReason = TEXT("");
    return true;
}

const FGlitchTask* AGlitch459PMGameMode::GetSelectedTask() const
{
    return CurrentLoopTasks.IsValidIndex(SelectedTaskIndex) ? &CurrentLoopTasks[SelectedTaskIndex] : nullptr;
}

FGlitchTask* AGlitch459PMGameMode::GetSelectedTaskMutable()
{
    return CurrentLoopTasks.IsValidIndex(SelectedTaskIndex) ? &CurrentLoopTasks[SelectedTaskIndex] : nullptr;
}

FString AGlitch459PMGameMode::BuildObjectDisplayName(const FName& ObjectId) const
{
    return ObjectId.ToString().Replace(TEXT("_"), TEXT(" "));
}

bool AGlitch459PMGameMode::TryUnlockShortcut(const FName& ShortcutId, const FString& DiscoveryMessage)
{
    if (ShortcutId.IsNone() || DiscoveredShortcuts.Contains(ShortcutId))
    {
        return false;
    }

    DiscoveredShortcuts.Add(ShortcutId);
    AddLog(DiscoveryMessage);
    return true;
}

void AGlitch459PMGameMode::HandleIntercomWhisper()
{
    const bool bShouldRunIntercom = CurrentLoop >= 8 || PressureLevel >= 3;
    if (!bShouldRunIntercom || CurrentSecond < NextIntercomSecond)
    {
        return;
    }

    const TArray<FString> IntercomLines = {
        TEXT("Arthur, your promotion packet is almost ready. Keep working."),
        TEXT("Arthur, the weekend is a privilege tier you have not unlocked."),
        TEXT("Arthur, we reviewed your resignation. It was denied retroactively."),
        TEXT("Arthur, productivity is how we measure the soul."),
        TEXT("Arthur, the Archive says you are improving."),
        TEXT("Arthur, your best years are still in this building.")
    };

    if (IntercomLines.Num() == 0)
    {
        return;
    }

    int32 NewLineIndex = FMath::RandRange(0, IntercomLines.Num() - 1);
    if (IntercomLines.Num() > 1)
    {
        while (NewLineIndex == LastIntercomLineIndex)
        {
            NewLineIndex = FMath::RandRange(0, IntercomLines.Num() - 1);
        }
    }

    LastIntercomLineIndex = NewLineIndex;
    bIntercomActiveThisLoop = true;
    AddLog(FString::Printf(TEXT("INTERCOM: %s"), *IntercomLines[NewLineIndex]));

    const int32 NextGap = 10 + FMath::RandRange(0, 8);
    NextIntercomSecond = FMath::Min(CurrentSecond + NextGap, LoopDurationSeconds - 2);
}

void AGlitch459PMGameMode::TickLoopSecond()
{
    if (HasEnded())
    {
        return;
    }

    ++CurrentSecond;
    HandleIntercomWhisper();

    if (CurrentSecond >= LoopDurationSeconds)
    {
        ResetLoop();
    }
}

void AGlitch459PMGameMode::ResetLoop()
{
    EvaluateLoopPressure();

    if (PressureLevel >= 5)
    {
        ++OverloadStrikes;
        AddLog(FString::Printf(TEXT("Overload strike %d/%d: the office is tightening around you."), OverloadStrikes, MaxOverloadStrikes));

        if (OverloadStrikes >= MaxOverloadStrikes)
        {
            bGameLost = true;
            EndingHeadline = TEXT("Still On The Clock");
            EndingBody = TEXT("The building promotes your body to furniture. 4:59 PM continues without you.");
            AddLog(TEXT("You are no longer an employee. You are infrastructure."));
            return;
        }
    }
    else if (bAnomalyFlaggedThisLoop)
    {
        OverloadStrikes = FMath::Max(OverloadStrikes - 1, 0);
    }

    ++CurrentLoop;
    CurrentSecond = 0;
    CurrentRoomId = TEXT("breakroom");
    SelectedObjectIndex = 0;
    SelectedExitIndex = 0;
    bAnomalyFlaggedThisLoop = false;
    bIntercomActiveThisLoop = false;
    NextIntercomSecond = 18 + FMath::RandRange(0, 8);

    PickNextAnomaly();
    BuildLoopTasks();
    ApplyNarrativeBeatForLoop();

    LastInspectionText = TEXT("The second hand hits 12. You blink, and the office resets to 4:59:00 PM.");
    AddLog(TEXT("The second hand hits 12. You blink. The clock snaps back to 4:59:00."));
}

FString AGlitch459PMGameMode::GetClockText() const
{
    return FString::Printf(TEXT("4:59:%02d PM"), CurrentSecond);
}

FString AGlitch459PMGameMode::GetNarrativeStageLabel() const
{
    if (CurrentLoop <= 10)
    {
        return TEXT("Normalcy Cracking");
    }

    if (CurrentLoop <= 13)
    {
        return TEXT("The Descent");
    }

    return TEXT("The Truth");
}

FString AGlitch459PMGameMode::GetCurrentRoomName() const
{
    const FGlitchRoom* Room = GetCurrentRoom();
    return Room ? Room->DisplayName : TEXT("Unknown Room");
}

FString AGlitch459PMGameMode::GetCurrentRoomDescription() const
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room)
    {
        return TEXT("Room data missing.");
    }

    if (CurrentLoop <= 10)
    {
        if (PressureLevel == 0)
        {
            return Room->Description;
        }

        return Room->Description + TEXT(" You feel watched by deadlines you missed.");
    }

    if (CurrentLoop <= 13)
    {
        if (PressureLevel >= 4)
        {
            return Room->Description + TEXT(" Distances shift and your heartbeat drowns the lights.");
        }

        return Room->Description + TEXT(" Distances shift when you stop looking directly at them.");
    }

    if (PressureLevel >= 4)
    {
        return Room->Description + TEXT(" The place feels less like architecture and more like a sentence being shouted." );
    }

    return Room->Description + TEXT(" The place feels less like architecture and more like a sentence.");
}

FString AGlitch459PMGameMode::GetSelectedObjectName() const
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Objects.IsEmpty())
    {
        return TEXT("None");
    }

    return BuildObjectDisplayName(Room->Objects[SelectedObjectIndex]);
}

FString AGlitch459PMGameMode::GetSelectedExitLabel() const
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Exits.IsEmpty())
    {
        return TEXT("No exits");
    }

    const FGlitchExit& Exit = Room->Exits[SelectedExitIndex];
    FString LockReason;
    if (!IsExitUnlocked(Exit, LockReason) && !Exit.bFinalExit)
    {
        return FString::Printf(TEXT("%s [LOCKED]"), *Exit.Label);
    }

    return Exit.Label;
}

FString AGlitch459PMGameMode::GetSelectedTaskPrompt() const
{
    const FGlitchTask* Task = GetSelectedTask();
    if (!Task)
    {
        return TEXT("No active tasks.");
    }

    const FString Prefix = Task->bSurreal ? TEXT("Surreal") : TEXT("Report");
    const FString Status = Task->bCompleted ? TEXT("DONE") : TEXT("PENDING");
    return FString::Printf(TEXT("%s Task: %s [%s]"), *Prefix, *Task->Prompt, *Status);
}

bool AGlitch459PMGameMode::IsSelectedTaskCompleted() const
{
    const FGlitchTask* Task = GetSelectedTask();
    return Task ? Task->bCompleted : false;
}

FString AGlitch459PMGameMode::GetSelectedObjectDescriptionAndClue()
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Objects.IsEmpty())
    {
        LastInspectionText = TEXT("There is nothing here.");
        return LastInspectionText;
    }

    const FName ObjectId = Room->Objects[SelectedObjectIndex];
    FString Description = ObjectDescriptions.FindRef(ObjectId);

    if (IsSelectedObjectAnomaly())
    {
        const FGlitchAnomaly* Anomaly = GetCurrentAnomaly();
        if (Anomaly)
        {
            Description = Anomaly->Description;
            AddLog(FString::Printf(TEXT("Anomaly clue: %s"), *Anomaly->Clue));
        }
    }

    if (CurrentRoomId == TEXT("breakroom") && ObjectId == TEXT("breakroom_door") && CurrentLoop >= 5)
    {
        TryUnlockShortcut(
            TEXT("shortcut_service_ladder"),
            TEXT("You pry open the breakroom vent. A service ladder bypass is now available.")
        );
    }

    if (CurrentRoomId == TEXT("lobby") && ObjectId == TEXT("security_camera") && CurrentLoop >= 8)
    {
        TryUnlockShortcut(
            TEXT("shortcut_fire_stair"),
            TEXT("You copy an executive badge pattern from the camera feed. Fire stair unlocked.")
        );
    }

    if (CurrentRoomId == TEXT("cubicles") && ObjectId == TEXT("desk_photo") && CurrentLoop >= 9)
    {
        TryUnlockShortcut(
            TEXT("shortcut_archive_chute"),
            TEXT("Behind the framed photo is a maintenance chute map. Archive shortcut unlocked.")
        );
    }

    LastInspectionText = Description;
    return LastInspectionText;
}

void AGlitch459PMGameMode::SelectNextObject()
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Objects.IsEmpty())
    {
        return;
    }

    SelectedObjectIndex = (SelectedObjectIndex + 1) % Room->Objects.Num();
}

void AGlitch459PMGameMode::SelectPreviousObject()
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Objects.IsEmpty())
    {
        return;
    }

    SelectedObjectIndex = (SelectedObjectIndex - 1 + Room->Objects.Num()) % Room->Objects.Num();
}

void AGlitch459PMGameMode::SelectNextExit()
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Exits.IsEmpty())
    {
        return;
    }

    SelectedExitIndex = (SelectedExitIndex + 1) % Room->Exits.Num();
}

void AGlitch459PMGameMode::SelectPreviousExit()
{
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Exits.IsEmpty())
    {
        return;
    }

    SelectedExitIndex = (SelectedExitIndex - 1 + Room->Exits.Num()) % Room->Exits.Num();
}

void AGlitch459PMGameMode::SelectNextTask()
{
    if (CurrentLoopTasks.IsEmpty())
    {
        return;
    }

    SelectedTaskIndex = (SelectedTaskIndex + 1) % CurrentLoopTasks.Num();
}

void AGlitch459PMGameMode::SelectPreviousTask()
{
    if (CurrentLoopTasks.IsEmpty())
    {
        return;
    }

    SelectedTaskIndex = (SelectedTaskIndex - 1 + CurrentLoopTasks.Num()) % CurrentLoopTasks.Num();
}

bool AGlitch459PMGameMode::TryFlagSelectedObject()
{
    if (HasEnded())
    {
        return false;
    }

    if (bAnomalyFlaggedThisLoop)
    {
        AddLog(TEXT("You already filed one anomaly report this loop."));
        return false;
    }

    if (IsSelectedObjectAnomaly())
    {
        bAnomalyFlaggedThisLoop = true;
        ResolvedAnomalies = FMath::Min(ResolvedAnomalies + 1, RequiredAnomalies);
        AddLog(TEXT("Anomaly flagged. Reality steadies for exactly one breath."));

        if (ResolvedAnomalies >= RequiredAnomalies && !bEndingHintLogged)
        {
            bEndingHintLogged = true;
            AddLog(TEXT("All required anomalies stabilized. One of these exits may finally tell the truth."));
        }

        return true;
    }

    AddLog(TEXT("False report. HR auto-reply: Thank you for your vigilance."));
    return false;
}

bool AGlitch459PMGameMode::TryCompleteSelectedTask()
{
    FGlitchTask* Task = GetSelectedTaskMutable();
    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Task || !Room || !Room->Objects.IsValidIndex(SelectedObjectIndex))
    {
        return false;
    }

    if (Task->bCompleted)
    {
        AddLog(TEXT("Task already completed this loop."));
        return false;
    }

    const FName SelectedObjectId = Room->Objects[SelectedObjectIndex];
    if (Task->RequiredRoom == CurrentRoomId && Task->RequiredObject == SelectedObjectId)
    {
        Task->bCompleted = true;
        ++CompletedTaskCount;
        AddLog(Task->CompletionText);
        return true;
    }

    AddLog(TEXT("Wrong terminal. Wrong form. Wrong room."));
    return false;
}

bool AGlitch459PMGameMode::TryUseSelectedExit()
{
    if (HasEnded())
    {
        return true;
    }

    const FGlitchRoom* Room = GetCurrentRoom();
    if (!Room || Room->Exits.IsEmpty())
    {
        return false;
    }

    const FGlitchExit& Exit = Room->Exits[SelectedExitIndex];

    if (Exit.bFinalExit)
    {
        if (ResolvedAnomalies >= RequiredAnomalies && CompletedTaskCount >= 8)
        {
            bGameWon = true;
            EndingHeadline = TEXT("Saturday");
            EndingBody = TEXT("The second hand crosses 12 and does not return. You leave the building as Arthur, not an employee number.");
            AddLog(TEXT("Saturday. The second hand crosses 12 and does not return."));
            AddLog(TEXT("Promotion status: irrelevant. You chose the weekend anyway."));
            return true;
        }

        if (CompletedTaskCount >= 12 && ResolvedAnomalies < RequiredAnomalies)
        {
            bGameWon = true;
            EndingHeadline = TEXT("Promotion Granted");
            EndingBody = TEXT("The doors open into a bigger office with no windows and no clock out button.");
            AddLog(TEXT("Congratulations, Arthur. Promotion approved."));
            AddLog(TEXT("Your new shift begins now."));
            return true;
        }

        CurrentRoomId = TEXT("breakroom");
        SelectedObjectIndex = 0;
        SelectedExitIndex = 0;
        AddLog(TEXT("The exit doors open into the breakroom. Again."));
        return false;
    }

    FString LockReason;
    if (!IsExitUnlocked(Exit, LockReason))
    {
        AddLog(Exit.LockedReason.IsEmpty() ? LockReason : Exit.LockedReason);
        return false;
    }

    CurrentRoomId = Exit.TargetRoom;
    SelectedObjectIndex = 0;
    SelectedExitIndex = 0;
    AddLog(FString::Printf(TEXT("You move to %s."), *GetCurrentRoomName()));
    return true;
}
