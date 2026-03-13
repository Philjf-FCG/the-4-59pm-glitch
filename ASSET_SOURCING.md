# Asset Sourcing Plan (Royalty-Free)

This project is set up to support royalty-free assets from FAB, Quixel Megascans, and CC0 libraries.

## Priority Atmosphere Assets

1. Fluorescent office hum loop
2. Heartbeat-like clock tick
3. HVAC rumble / electric buzz
4. Corporate office material set (carpet tiles, ceiling panels, cubicle fabric)
5. Vintage office props (water cooler, printer, desk phone, CRT monitor)

## Recommended Sources

- FAB (free and licensed packs): office props, ambience loops, horror stingers
- Quixel Megascans (included with Unreal ecosystem): concrete, industrial, and rough interior surfaces
- CC0 audio libraries (for fallback ambience): neutral room tones, mechanical hum, clock ticks

## Suggested Content Folder Layout

- Content/Audio/Ambience
- Content/Audio/Stingers
- Content/Audio/VO
- Content/Materials/Office
- Content/Meshes/Office
- Content/Decals/Anomalies

## Integration Targets In Current C++ Logic

- Room identity and progression: Source/Glitch459PM/Glitch459PMGameMode.cpp
- Player movement and sprint pacing: Source/Glitch459PM/Glitch459PMPawn.cpp
- On-screen loop/task feedback: Source/Glitch459PM/Glitch459PMHUD.cpp

## Asset Acceptance Checklist

- Confirm license allows commercial use and redistribution in packaged games.
- Keep attribution notes in this file when required by source license.
- Normalize loudness for ambience and stingers to avoid clipping.
- Use looping cues for hum/heartbeat and one-shot cues for anomaly reveals.

## Attribution Log

- Add entries here as assets are imported.
- Format: Asset Name | Source URL | License | Notes
