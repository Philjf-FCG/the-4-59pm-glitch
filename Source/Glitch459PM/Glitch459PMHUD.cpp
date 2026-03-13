#include "Glitch459PMHUD.h"

#include "Glitch459PMGameMode.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "Engine/World.h"

void AGlitch459PMHUD::DrawHUD()
{
    Super::DrawHUD();

    UWorld* World = GetWorld();
    AGlitch459PMGameMode* GameMode = World ? Cast<AGlitch459PMGameMode>(World->GetAuthGameMode()) : nullptr;
    if (!GameMode || !Canvas)
    {
        return;
    }

    UFont* Font = GEngine ? GEngine->GetSmallFont() : nullptr;
    if (!Font)
    {
        return;
    }

    float X = 32.0f;
    float Y = 28.0f;

    DrawText(FString::Printf(TEXT("Current Time: %s"), *GameMode->GetClockText()), FLinearColor(1.0f, 0.92f, 0.7f), X, Y, Font, 1.35f);
    Y += 34.0f;

    DrawText(
        FString::Printf(TEXT("Loop: %d    Anomalies Stabilized: %d/%d"), GameMode->GetCurrentLoop(), GameMode->GetResolvedAnomalies(), GameMode->GetRequiredAnomalies()),
        FLinearColor(0.78f, 0.9f, 0.83f),
        X,
        Y,
        Font,
        1.1f
    );
    Y += 42.0f;

    DrawText(
        FString::Printf(
            TEXT("Stage: %s    Tasks: %d    Shortcuts: %d    Pressure: %d/5"),
            *GameMode->GetNarrativeStageLabel(),
            GameMode->GetCompletedTaskCount(),
            GameMode->GetDiscoveredShortcutCount(),
            GameMode->GetPressureLevel()
        ),
        FLinearColor(0.9f, 0.78f, 0.74f),
        X,
        Y,
        Font,
        1.0f
    );
    Y += 28.0f;

    DrawText(FString::Printf(TEXT("Room: %s"), *GameMode->GetCurrentRoomName()), FLinearColor::White, X, Y, Font, 1.1f);
    Y += 24.0f;
    DrawText(GameMode->GetCurrentRoomDescription(), FLinearColor(0.84f, 0.9f, 0.87f), X, Y, Font, 1.0f);
    Y += 48.0f;

    DrawText(FString::Printf(TEXT("Focused Object: %s"), *GameMode->GetSelectedObjectName()), FLinearColor(0.96f, 0.8f, 0.75f), X, Y, Font, 1.0f);
    Y += 24.0f;
    DrawText(FString::Printf(TEXT("Selected Exit: %s"), *GameMode->GetSelectedExitLabel()), FLinearColor(0.75f, 0.88f, 1.0f), X, Y, Font, 1.0f);
    Y += 24.0f;
    DrawText(GameMode->GetSelectedTaskPrompt(), FLinearColor(0.92f, 0.7f, 0.7f), X, Y, Font, 1.0f);
    Y += 24.0f;
    DrawText(FString::Printf(TEXT("Inspection: %s"), *GameMode->GetLastInspectionText()), FLinearColor(0.82f, 0.9f, 0.96f), X, Y, Font, 0.95f);
    Y += 30.0f;

    DrawText(TEXT("Controls: Q/E object  R/T exit  Z/C task  Tab inspect  F flag anomaly  X complete task  Enter use exit"), FLinearColor(0.62f, 0.73f, 0.68f), X, Y, Font, 0.95f);
    Y += 36.0f;

    DrawText(TEXT("Internal Monologue:"), FLinearColor(0.9f, 0.97f, 0.93f), X, Y, Font, 1.0f);
    Y += 24.0f;

    const TArray<FString>& LogLines = GameMode->GetLogLines();
    for (const FString& Line : LogLines)
    {
        DrawText(Line, FLinearColor(0.72f, 0.82f, 0.78f), X, Y, Font, 0.95f);
        Y += 20.0f;
    }

    if (GameMode->HasWon())
    {
        const FString WinMessage = TEXT("Saturday. The second hand passes 12 and keeps moving.");
        const float CenterX = Canvas->ClipX * 0.5f - 280.0f;
        const float CenterY = Canvas->ClipY * 0.8f;
        DrawText(WinMessage, FLinearColor(1.0f, 0.95f, 0.7f), CenterX, CenterY, Font, 1.2f);
    }
}
