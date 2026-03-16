import argparse
import json
import math
import random
import struct
import subprocess
import sys
import textwrap
import wave
from pathlib import Path


DEFAULT_SAMPLE_RATE = 24000


def clamp_sample(value: float) -> float:
    return max(-1.0, min(1.0, value))


def write_wave16_mono(path: Path, samples: list[float], sample_rate: int) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with wave.open(str(path), "wb") as wav_file:
        wav_file.setnchannels(1)
        wav_file.setsampwidth(2)
        wav_file.setframerate(sample_rate)

        frames = bytearray()
        for sample in samples:
            frames.extend(struct.pack("<h", int(clamp_sample(sample) * 32767.0)))
        wav_file.writeframes(bytes(frames))


def build_signal(duration_seconds: float, sample_rate: int, sample_fn) -> list[float]:
    sample_count = int(duration_seconds * sample_rate)
    return [sample_fn(index / sample_rate) for index in range(sample_count)]


def generate_hvac_hum(sample_rate: int) -> list[float]:
    return build_signal(
        8.0,
        sample_rate,
        lambda t: (
            0.26 * math.sin(2.0 * math.pi * 58.0 * t)
            + 0.12 * math.sin(2.0 * math.pi * 116.0 * t)
            + 0.025 * random.uniform(-1.0, 1.0)
        )
        * (0.92 + 0.08 * math.sin(2.0 * math.pi * 0.17 * t)),
    )


def generate_fluorescent_buzz(sample_rate: int) -> list[float]:
    return build_signal(
        8.0,
        sample_rate,
        lambda t: (
            0.17 * math.sin(2.0 * math.pi * 120.0 * t)
            + 0.09 * math.sin(2.0 * math.pi * 240.0 * t)
            + 0.02 * random.uniform(-1.0, 1.0)
        )
        * (0.82 + 0.18 * math.sin(2.0 * math.pi * 7.0 * t)),
    )


def generate_clock_tick(sample_rate: int) -> list[float]:
    def sample_fn(t: float) -> float:
        local_t = t % 1.0
        tick = 0.0
        if local_t < 0.12:
            envelope = math.exp(-42.0 * local_t)
            tick = 0.72 * math.sin(2.0 * math.pi * 1900.0 * local_t) * envelope
            tick += 0.20 * math.sin(2.0 * math.pi * 980.0 * local_t) * envelope
        return tick + 0.03 * math.sin(2.0 * math.pi * 55.0 * t)

    return build_signal(6.0, sample_rate, sample_fn)


def generate_office_dread_bed(sample_rate: int) -> list[float]:
    return build_signal(
        10.0,
        sample_rate,
        lambda t: (
            0.22 * math.sin(2.0 * math.pi * 42.0 * t)
            + 0.08 * math.sin(2.0 * math.pi * 84.0 * t)
            + 0.02 * random.uniform(-1.0, 1.0)
        )
        * (0.90 + 0.04 * math.sin(2.0 * math.pi * 0.09 * t)),
    )


def generate_intercom_crackle(sample_rate: int) -> list[float]:
    return build_signal(
        2.0,
        sample_rate,
        lambda t: (
            (0.80 * random.uniform(-1.0, 1.0) if random.randint(0, 99) < 12 else 0.0)
            + 0.12 * math.sin(2.0 * math.pi * 880.0 * t)
        )
        * math.exp(-2.8 * t),
    )


def generate_pressure_rise(sample_rate: int) -> list[float]:
    def sample_fn(t: float) -> float:
        duration = 3.0
        progress = t / duration
        frequency = 90.0 + 220.0 * progress
        envelope = progress**1.4
        return (
            0.4 * math.sin(2.0 * math.pi * frequency * t)
            + 0.05 * random.uniform(-1.0, 1.0)
        ) * envelope

    return build_signal(3.0, sample_rate, sample_fn)


def synthesize_voice_line(text: str, output_path: Path) -> None:
    escaped_path = str(output_path).replace("'", "''")
    escaped_text = text.replace("'", "''")
    powershell_script = textwrap.dedent(
        f"""
        Add-Type -AssemblyName System.Speech
        $synth = New-Object System.Speech.Synthesis.SpeechSynthesizer
        $preferred = $synth.GetInstalledVoices() |
            ForEach-Object {{ $_.VoiceInfo.Name }} |
            Where-Object {{ $_ -match 'Zira|David|Mark' }} |
            Select-Object -First 1
        if ($preferred) {{
            $synth.SelectVoice($preferred)
        }}
        $synth.Rate = -2
        $synth.Volume = 90
        $synth.SetOutputToWaveFile('{escaped_path}')
        $synth.Speak('{escaped_text}')
        $synth.SetOutputToNull()
        $synth.Dispose()
        """
    ).strip()

    result = subprocess.run(
        [
            "powershell.exe",
            "-NoProfile",
            "-NonInteractive",
            "-ExecutionPolicy",
            "Bypass",
            "-Command",
            powershell_script,
        ],
        capture_output=True,
        text=True,
        check=False,
    )
    if result.returncode != 0:
        error_text = result.stderr.strip() or result.stdout.strip() or f"exit code {result.returncode}"
        raise RuntimeError(error_text)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Generate first-pass ambience, stingers, and intercom VO WAVs.")
    parser.add_argument("--output-root", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--sample-rate", type=int, default=DEFAULT_SAMPLE_RATE)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    random.seed(459)

    ambience_dir = args.output_root / "Ambience"
    stingers_dir = args.output_root / "Stingers"
    voice_dir = args.output_root / "VO" / "Intercom"

    for directory in (ambience_dir, stingers_dir, voice_dir):
        directory.mkdir(parents=True, exist_ok=True)

    write_wave16_mono(ambience_dir / "A_HVACHum.wav", generate_hvac_hum(args.sample_rate), args.sample_rate)
    write_wave16_mono(ambience_dir / "A_ClockTick.wav", generate_clock_tick(args.sample_rate), args.sample_rate)
    write_wave16_mono(ambience_dir / "A_FluorescentBuzz.wav", generate_fluorescent_buzz(args.sample_rate), args.sample_rate)
    write_wave16_mono(ambience_dir / "A_OfficeDreadBed.wav", generate_office_dread_bed(args.sample_rate), args.sample_rate)
    write_wave16_mono(stingers_dir / "A_IntercomCrackle.wav", generate_intercom_crackle(args.sample_rate), args.sample_rate)
    write_wave16_mono(stingers_dir / "A_PressureRise.wav", generate_pressure_rise(args.sample_rate), args.sample_rate)

    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    voice_failures: list[tuple[str, str]] = []
    for line in manifest.get("lines", []):
        output_path = voice_dir / f"{line['key']}.wav"
        try:
            synthesize_voice_line(line["text"], output_path)
        except RuntimeError as exc:
            voice_failures.append((line["key"], str(exc)))

    print(f"Generated ambience WAVs: {len(list(ambience_dir.glob('*.wav')))}")
    print(f"Generated stinger WAVs: {len(list(stingers_dir.glob('*.wav')))}")
    print(f"Generated voice WAVs: {len(list(voice_dir.glob('*.wav')))}")

    if voice_failures:
        for key, failure in voice_failures:
            print(f"VOICE ERROR {key}: {failure}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())