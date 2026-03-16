import os
import unreal


ROOT = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(ROOT, ".."))
SOURCE_ROOT = os.path.join(PROJECT_ROOT, "ExternalAssets", "GeneratedAudio")

IMPORT_MAP = {
    os.path.join(SOURCE_ROOT, "Ambience"): "/Game/Audio/Ambience",
    os.path.join(SOURCE_ROOT, "Stingers"): "/Game/Audio/Stingers",
    os.path.join(SOURCE_ROOT, "VO", "Intercom"): "/Game/Audio/VO/Intercom",
}


def import_directory(source_dir: str, destination_path: str) -> int:
    if not os.path.isdir(source_dir):
        unreal.log_warning(f"Source directory missing: {source_dir}")
        return 0

    wav_files = [
        os.path.join(source_dir, name)
        for name in os.listdir(source_dir)
        if name.lower().endswith(".wav")
    ]

    if not wav_files:
        unreal.log_warning(f"No WAV files found in {source_dir}")
        return 0

    tasks = []
    for wav_file in wav_files:
        task = unreal.AssetImportTask()
        task.filename = wav_file
        task.destination_path = destination_path
        task.automated = True
        task.replace_existing = True
        task.save = True
        tasks.append(task)

    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks(tasks)
    unreal.EditorAssetLibrary.save_directory(destination_path, only_if_is_dirty=False, recursive=True)
    unreal.log(f"Imported {len(tasks)} WAV files to {destination_path}")
    return len(tasks)


def main() -> None:
    imported_count = 0
    for source_dir, destination_path in IMPORT_MAP.items():
        imported_count += import_directory(source_dir, destination_path)
    unreal.log(f"Audio import complete. Imported {imported_count} assets.")


if __name__ == "__main__":
    main()