# Asset Sourcing Plan (Royalty-Free)

This project is set up to support royalty-free assets from FAB, Quixel Megascans, and CC0 libraries.

## Priority Atmosphere Assets

1. Fluorescent office hum loop
2. Heartbeat-like clock tick
3. HVAC rumble / electric buzz
4. Corporate office material set (carpet tiles, ceiling panels, cubicle fabric)
5. Vintage office props (water cooler, printer, desk phone, CRT monitor)

## Suggested Audio Asset Names

- `Content/Audio/Ambience/A_HVACHum`
- `Content/Audio/Ambience/A_ClockTick`
- `Content/Audio/Ambience/A_FluorescentBuzz`
- `Content/Audio/Ambience/A_OfficeDreadBed`
- `Content/Audio/Stingers/A_IntercomCrackle`
- `Content/Audio/Stingers/A_PressureRise`

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

## Voice Synthesis Workflow

- This repo now supports keyed intercom voice clips such as `neutral_01`, `obedient_03`, and `defiant_02` through the office-shell audio hooks.
- If you want natural TTS from Gemini TTS or another vendor, generate mono or stereo WAV files at 48 kHz and import them to `Content/Audio/VO/Intercom`.
- Name each imported Unreal asset exactly after the key in the manifest so it auto-resolves at runtime without manual mapping.
- Match each imported asset to its key in the `IntercomVoiceAssets` array on the spawned `Glitch459PMOfficeShell` actor or a derived Blueprint.
- Use the manifest in `Scripts/intercom_tts_manifest.json` as the canonical line list for synthesis.
- Use `Scripts/Validate-IntercomVoiceAssets.ps1` to check which required clips are still missing after import.
- Recommended voice direction: calm corporate manager, slight smile, low warmth, subtle contempt, no theatrical monster processing in the source audio.

## Attribution Log

- Add entries here as assets are imported.
- Format: Asset Name | Source URL | License | Notes
- SBS Horror Texture Pack 512x512 | User-provided archive in project root | See included License.txt | Imported selected wall, ceiling, floor, metal, and accent textures into /Game/Horror for fallback room and terminal materials.
