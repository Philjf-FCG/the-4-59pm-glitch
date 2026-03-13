# The 4:59PM Glitch

The 4:59 PM Glitch (Psychological Horror)

In this first-person narrative game, you are an office worker waiting for the clock to strike 5:00 PM so you can start your weekend. But every time the second hand hits 12, the clock resets to 4:59:00.

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

- Time starts at `4:59:00 PM` and advances each second.
- At `4:59:59 -> 4:59:00`, the loop resets.
- One anomaly is active each loop.
- Correctly flag anomalies to stabilize reality.
- Complete loop tasks from Arthur's "Final Friday Report" board.
- Unlock deeper routes (server room, CEO office, Archive) with loop knowledge and completed tasks.
- Escape requires both anomaly mastery and report progress.

### Narrative Structure

- **The First 10 Loops**: normal office details start drifting.
- **The Descent**: office geometry and chronology destabilize.
- **The Truth**: Arthur discovers The Archive and the cost of perpetual productivity.

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
- `Config/DefaultInput.ini`: key mappings
- `Config/DefaultGame.ini`: default game mode wiring
- `ASSET_SOURCING.md`: royalty-free asset integration plan and attribution log
