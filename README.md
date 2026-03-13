# The 4:59PM Glitch

The 4:59 PM Glitch (Psychological Horror)

In this first-person narrative game, you are an office worker waiting for the clock to strike 5:00 PM so you can start your weekend. But every time the clock reaches 5:00, the office snaps back to 4:57:00.

The Hook: The office starts to distort. The water cooler grows tentacles, coworkers repeat the same banal jokes until they become screams, and the exit doors lead back into the breakroom.

Gameplay: A "loop-based" puzzle game (think P.T.). You must find "anomalies" in the office to break the cycle and finally reach Saturday.

The Vibe: Corporate surrealism, fluorescent lights, and the ticking of a clock that sounds like a heartbeat.

## Unreal Engine 5.6.1 Prototype

This repository now contains an Unreal Engine C++ implementation (UE 5.6.1).

### Setup

1. Install Unreal Engine `5.6.1`.
2. Right-click `The459PMGlitch.uproject` and choose `Generate Visual Studio project files`.
3. Open the generated solution and build `Development Editor | Win64`.
4. Open `The459PMGlitch.uproject` in UE.
5. Press Play (PIE).

### Gameplay Loop

- Time starts at `4:57:00 PM` and advances each second.
- At `4:59:59 -> 4:57:00`, the loop resets.
- One anomaly is active each loop.
- Correctly flag anomalies to stabilize reality.
- Complete loop tasks from Arthur's "Final Friday Report" board.
- Unlock deeper routes (server room, CEO office, Archive) with loop knowledge and completed tasks.
- Discover hidden shortcuts by inspecting the right objects on later loops.
- Recover memory fragments from key objects to unlock Arthur's full escape route.
- Keep momentum each loop or pressure rises and descriptions become more hostile.
- Escape requires both anomaly mastery and report progress.

### How To Play

1. Start in the breakroom at `4:57:00 PM` and use the HUD to identify your selected object, exit, task, premonition, and loop directive.
2. Inspect suspicious objects with `Tab` to gather clues, reveal shortcuts, and recover memory fragments on later loops.
3. Use `F` only when you are confident the selected object is the active anomaly. False reports raise pressure immediately.
4. Use `Z / C` to select a task, move to the required room and object, then press `X` to complete it.
5. Watch the current directive. Obeying it lowers pressure and improves compliance; missing it makes later loops harsher.
6. Compliance now matters beyond survival: high obedience changes intercom behavior and is required for the corporate promotion ending.
7. Use exits to unlock deeper routes through the office. Some exits need loop knowledge, completed tasks, or discovered shortcuts.
8. Review the new loop-review line after every reset. It tells you whether you actually made progress before the clock snapped back.
9. To reach the best ending, combine anomaly stabilization, task progress, and all memory fragments before taking the lobby exit.
10. Recent anomalies and tasks are rotated to avoid immediate repetition, so later loops should expose more of the office before the cycle repeats.

### Narrative Structure

- **The First 10 Loops**: normal office details start drifting.
- **The Descent**: office geometry and chronology destabilize.
- **The Truth**: Arthur discovers The Archive and the cost of perpetual productivity.

### Systems Added In Latest Iteration

- **Shortcut Discovery**: inspecting key objects can unlock service routes that persist across loops.
- **Pressure Meter**: unproductive loops increase pressure; successful loops reduce it.
- **Escalating Atmosphere Text**: room descriptions react to both stage and pressure level.
- **Intercom Intrusions**: pressure and late loops trigger boss voice interruptions with personalized taunts.
- **Branching End States**: true Saturday escape, corporate "promotion" trap ending, and overload collapse failure.
- **Adaptive Loop Duration**: rising pressure can compress the three-minute loop down to two minutes, increasing urgency and route planning demands.
- **Reachability-Safe Task Picks**: loop task generation now favors objectives the player can actually reach in that loop.
- **Memory Fragments**: inspect late-loop objects to recover Arthur's personal memories and unlock a superior ending path.
- **Premonitions**: each loop starts with a hint about reality drift; low pressure gives reliable clues, high pressure corrupts them.
- **Anomaly Report Risk**: false reports immediately raise pressure while correct reports can calm it.
- **Diegetic Status Terminal**: a placeable actor can mirror loop status, tasks, anomaly count, and restored-memory state directly in the world.
- **Compliance Directives**: each loop can issue a specific order like reaching a room, inspecting an object, or stabilizing the anomaly; obeying it reduces pressure, ignoring it adds risk.
- **Compliance Consequences**: obedience now changes intercom tone and gates the corporate promotion branch.
- **Room-Specific Distortion**: pressure no longer escalates with only generic text; each room now mutates in its own way as the office destabilizes.
- **Loop Review**: every reset now records what you achieved or missed, making failed loops easier to read and correct.
- **Content Rotation**: anomalies cycle through the deck before repeating, and tasks avoid immediate back-to-back duplicates when alternatives exist.

### Controls (DefaultInput.ini)

- `W / A / S / D`: Move (first-person)
- `Mouse`: Look
- `Left Shift`: Sprint
- `Q / E`: Previous or next object
- `R / T`: Previous or next exit
- `Z / C`: Previous or next task
- `Tab`: Inspect selected object
- `F`: Flag selected object as anomaly
- `X`: Complete selected task (if at the right room/object)
- `Enter`: Use selected exit

### Code Structure

- `Source/Glitch459PM/Glitch459PMGameMode.*`: loop timer, room graph, anomaly deck, puzzle progression, narrative stages, task board
- `Source/Glitch459PM/Glitch459PMPlayerController.*`: input bindings and player actions
- `Source/Glitch459PM/Glitch459PMPawn.*`: first-person movement and sprint pacing
- `Source/Glitch459PM/Glitch459PMHUD.*`: on-screen narrative HUD, loop/task/status display
- `Source/Glitch459PM/Glitch459PMStatusTerminal.*`: placeable in-world terminal actor that displays live loop state
- `Config/DefaultInput.ini`: key mappings
- `Config/DefaultGame.ini`: default game mode wiring
- `ASSET_SOURCING.md`: royalty-free asset integration plan and attribution log
