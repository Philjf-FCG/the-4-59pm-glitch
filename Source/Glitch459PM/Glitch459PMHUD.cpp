#include "Glitch459PMHUD.h"

#include "Glitch459PMGameMode.h"
#include "Engine/Canvas.h"
#include "CanvasItem.h"
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

    const float PanelMarginX = 24.0f;
    const float PanelMarginY = 22.0f;
    const float PanelWidth = FMath::Min(Canvas->ClipX * 0.58f, 760.0f);
    const float PanelHeight = Canvas->ClipY - (PanelMarginY * 2.0f);
    const float PanelX = PanelMarginX;
    const float PanelY = PanelMarginY;
    const float BezelThickness = 16.0f;
    const float InnerInset = 18.0f;

    const float TimePhase = World->GetTimeSeconds();
    const float TextJitterX = 0.55f * FMath::Sin(TimePhase * 9.0f) + 0.22f * FMath::Sin(TimePhase * 21.0f);
    const float TextJitterY = 0.35f * FMath::Cos(TimePhase * 8.0f) + 0.15f * FMath::Sin(TimePhase * 17.0f);

    const FLinearColor OuterHousingColor(0.2f, 0.19f, 0.17f, 0.95f);
    const FLinearColor BezelColor(0.72f, 0.67f, 0.55f, 0.97f);
    const FLinearColor BezelShadeColor(0.50f, 0.45f, 0.35f, 0.85f);
    const FLinearColor BezelHighlightColor(0.87f, 0.83f, 0.72f, 0.45f);
    const FLinearColor BezelCreaseColor(0.35f, 0.30f, 0.22f, 0.55f);
    const FLinearColor ScreenColor(0.01f, 0.02f, 0.01f, 0.94f);
    const FLinearColor PhosphorPrimary(0.48f, 1.0f, 0.56f, 1.0f);
    const FLinearColor PhosphorSecondary(0.25f, 0.82f, 0.34f, 1.0f);
    const FLinearColor PhosphorDim(0.20f, 0.52f, 0.24f, 1.0f);

    DrawRect(OuterHousingColor, PanelX - 8.0f, PanelY - 8.0f, PanelWidth + 16.0f, PanelHeight + 16.0f);
    DrawRect(FLinearColor(0.06f, 0.06f, 0.06f, 0.42f), PanelX + 8.0f, PanelY + PanelHeight + 6.0f, PanelWidth + 16.0f, 12.0f);
    DrawRect(BezelColor, PanelX, PanelY, PanelWidth, PanelHeight);
    DrawRect(BezelShadeColor, PanelX, PanelY + PanelHeight - 14.0f, PanelWidth, 14.0f);
    DrawRect(BezelShadeColor, PanelX + PanelWidth - 14.0f, PanelY, 14.0f, PanelHeight);
    DrawRect(BezelHighlightColor, PanelX + 6.0f, PanelY + 6.0f, PanelWidth - 20.0f, 4.0f);
    DrawRect(BezelHighlightColor, PanelX + 6.0f, PanelY + 6.0f, 4.0f, PanelHeight - 20.0f);
    DrawRect(BezelCreaseColor, PanelX + 12.0f, PanelY + 12.0f, PanelWidth - 24.0f, 1.5f);

    const float ScreenX = PanelX + BezelThickness;
    const float ScreenY = PanelY + BezelThickness;
    const float ScreenW = PanelWidth - (BezelThickness * 2.0f);
    const float ScreenH = PanelHeight - (BezelThickness * 2.0f);
    DrawRect(ScreenColor, ScreenX, ScreenY, ScreenW, ScreenH);

    for (int32 ScrewIdx = 0; ScrewIdx < 4; ++ScrewIdx)
    {
        const float ScrewInsetX = (ScrewIdx % 2 == 0) ? 8.0f : (PanelWidth - 16.0f);
        const float ScrewInsetY = (ScrewIdx < 2) ? 8.0f : (PanelHeight - 16.0f);
        DrawRect(FLinearColor(0.30f, 0.27f, 0.21f, 0.95f), PanelX + ScrewInsetX, PanelY + ScrewInsetY, 8.0f, 8.0f);
        DrawRect(FLinearColor(0.45f, 0.41f, 0.33f, 0.8f), PanelX + ScrewInsetX + 1.0f, PanelY + ScrewInsetY + 1.0f, 6.0f, 1.0f);
    }

    const float HeaderHeight = 32.0f;
    DrawRect(FLinearColor(0.02f, 0.14f, 0.04f, 0.95f), ScreenX, ScreenY, ScreenW, HeaderHeight);

    for (int32 Glow = 0; Glow < 5; ++Glow)
    {
        const float Inset = 6.0f + (Glow * 8.0f);
        const float Alpha = 0.045f - (Glow * 0.007f);
        DrawRect(FLinearColor(0.10f, 0.55f, 0.20f, FMath::Max(0.0f, Alpha)), ScreenX + Inset, ScreenY + Inset, ScreenW - (Inset * 2.0f), ScreenH - (Inset * 2.0f));
    }

    for (float ScanY = ScreenY + HeaderHeight; ScanY < ScreenY + ScreenH; ScanY += 4.0f)
    {
        DrawRect(FLinearColor(0.0f, 0.09f, 0.03f, 0.18f), ScreenX + 2.0f, ScanY, ScreenW - 4.0f, 1.0f);
    }

    // Corner masks fake curved CRT glass and soften readability falloff near edges.
    for (int32 Step = 0; Step < 14; ++Step)
    {
        const float Size = 8.0f + (Step * 7.0f);
        const float Alpha = 0.13f - (Step * 0.007f);
        const FLinearColor CornerMask(0.0f, 0.0f, 0.0f, FMath::Max(0.0f, Alpha));
        DrawRect(CornerMask, ScreenX, ScreenY, Size, Size);
        DrawRect(CornerMask, ScreenX + ScreenW - Size, ScreenY, Size, Size);
        DrawRect(CornerMask, ScreenX, ScreenY + ScreenH - Size, Size, Size);
        DrawRect(CornerMask, ScreenX + ScreenW - Size, ScreenY + ScreenH - Size, Size, Size);
    }

    for (int32 Step = 0; Step < 6; ++Step)
    {
        const float Cut = 6.0f + (Step * 4.0f);
        DrawRect(BezelColor, ScreenX, ScreenY, Cut, Cut);
        DrawRect(BezelColor, ScreenX + ScreenW - Cut, ScreenY, Cut, Cut);
        DrawRect(BezelColor, ScreenX, ScreenY + ScreenH - Cut, Cut, Cut);
        DrawRect(BezelColor, ScreenX + ScreenW - Cut, ScreenY + ScreenH - Cut, Cut, Cut);
    }

    auto MeasureTextWidth = [this, Font](const FString& Text, float Scale) -> float
    {
        float RawW = 0.0f;
        float RawH = 0.0f;
        Canvas->StrLen(Font, Text, RawW, RawH);
        return RawW * Scale;
    };

    auto WrapTextToWidth = [MeasureTextWidth](const FString& Text, float Scale, float MaxWidth) -> TArray<FString>
    {
        TArray<FString> WrappedLines;
        TArray<FString> SourceLines;
        Text.ParseIntoArrayLines(SourceLines, true);

        for (const FString& SourceLine : SourceLines)
        {
            TArray<FString> Words;
            SourceLine.ParseIntoArrayWS(Words);

            if (Words.Num() == 0)
            {
                WrappedLines.Add(TEXT(" "));
                continue;
            }

            FString CurrentLine;
            for (const FString& Word : Words)
            {
                const FString Candidate = CurrentLine.IsEmpty() ? Word : CurrentLine + TEXT(" ") + Word;
                if (MeasureTextWidth(Candidate, Scale) <= MaxWidth)
                {
                    CurrentLine = Candidate;
                    continue;
                }

                if (!CurrentLine.IsEmpty())
                {
                    WrappedLines.Add(CurrentLine);
                    CurrentLine.Empty();
                }

                CurrentLine = Word;
                while (MeasureTextWidth(CurrentLine, Scale) > MaxWidth && CurrentLine.Len() > 4)
                {
                    int32 CutIndex = CurrentLine.Len() - 1;
                    while (CutIndex > 3 && MeasureTextWidth(CurrentLine.Left(CutIndex) + TEXT("-"), Scale) > MaxWidth)
                    {
                        --CutIndex;
                    }

                    WrappedLines.Add(CurrentLine.Left(CutIndex) + TEXT("-"));
                    CurrentLine = CurrentLine.RightChop(CutIndex);
                }
            }

            if (!CurrentLine.IsEmpty())
            {
                WrappedLines.Add(CurrentLine);
            }
        }

        return WrappedLines;
    };

    auto DrawPhosphorText = [this, Font, TextJitterX, TextJitterY](const FString& Text, const FLinearColor& Color, float XPos, float YPos, float Scale)
    {
        const FLinearColor Bloom(Color.R * 0.35f, Color.G * 0.95f, Color.B * 0.35f, 0.22f);
        DrawText(Text, Bloom, XPos + TextJitterX - 1.0f, YPos + TextJitterY, Font, Scale);
        DrawText(Text, Bloom, XPos + TextJitterX + 1.0f, YPos + TextJitterY, Font, Scale);
        DrawText(Text, Bloom, XPos + TextJitterX, YPos + TextJitterY - 1.0f, Font, Scale);
        DrawText(Text, Bloom, XPos + TextJitterX, YPos + TextJitterY + 1.0f, Font, Scale);
        DrawText(Text, Color, XPos + TextJitterX, YPos + TextJitterY, Font, Scale);
    };

    auto DrawWrappedPhosphorText = [WrapTextToWidth, DrawPhosphorText](
        const FString& Text,
        const FLinearColor& Color,
        float XPos,
        float& InOutY,
        float Scale,
        float MaxWidth,
        float ExtraLineSpacing
    )
    {
        const TArray<FString> Lines = WrapTextToWidth(Text, Scale, MaxWidth);
        const float BaseLineAdvance = 18.0f * Scale;
        for (const FString& Line : Lines)
        {
            DrawPhosphorText(Line, Color, XPos, InOutY, Scale);
            InOutY += BaseLineAdvance;
        }

        InOutY += ExtraLineSpacing;
    };

    float X = ScreenX + InnerInset;
    float Y = ScreenY + 6.0f;
    const float TextMaxWidth = ScreenW - (InnerInset * 2.0f) - 8.0f;
    const float ContentBottomY = ScreenY + ScreenH - 10.0f;

    auto DrawClippedWrappedBlock = [&DrawWrappedPhosphorText, ContentBottomY](const FString& Text, const FLinearColor& Color, float XPos, float& InOutY, float Scale, float MaxWidth, float ExtraSpacing)
    {
        if (InOutY >= ContentBottomY)
        {
            return;
        }

        DrawWrappedPhosphorText(Text, Color, XPos, InOutY, Scale, MaxWidth, ExtraSpacing);
        InOutY = FMath::Min(InOutY, ContentBottomY);
    };

    DrawClippedWrappedBlock(TEXT("OPS PRODUCTIVITY SUITE // CRT-459"), PhosphorPrimary, X, Y, 1.0f, TextMaxWidth, 2.0f);
    DrawClippedWrappedBlock(TEXT("SYNC: INTERNAL COMPLIANCE MONITOR"), PhosphorDim, X, Y, 0.9f, TextMaxWidth, 10.0f);

    DrawClippedWrappedBlock(FString::Printf(TEXT("TIME      | %s"), *GameMode->GetClockText()), PhosphorPrimary, X, Y, 1.2f, TextMaxWidth, 6.0f);

    DrawClippedWrappedBlock(FString::Printf(TEXT("LOOP      | %d      STABILIZED | %d / %d"), GameMode->GetCurrentLoop(), GameMode->GetResolvedAnomalies(), GameMode->GetRequiredAnomalies()), PhosphorSecondary, X, Y, 0.95f, TextMaxWidth, 2.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("STAGE     | %s    TASKS | %d    COMPLIANCE | %d"), *GameMode->GetNarrativeStageLabel(), GameMode->GetCompletedTaskCount(), GameMode->GetComplianceScore()), PhosphorSecondary, X, Y, 0.9f, TextMaxWidth, 2.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("SHORTCUTS | %d    FRAGMENTS | %d/%d    PRESSURE | %d/5    T-%ds"), GameMode->GetDiscoveredShortcutCount(), GameMode->GetCollectedFragmentCount(), GameMode->GetRequiredFragmentCount(), GameMode->GetPressureLevel(), GameMode->GetSecondsRemaining()), PhosphorSecondary, X, Y, 0.9f, TextMaxWidth, 10.0f);

    DrawClippedWrappedBlock(FString::Printf(TEXT("INTERCOM  | %s"), GameMode->IsIntercomActiveThisLoop() ? TEXT("ACTIVE") : TEXT("QUIET")), PhosphorPrimary, X, Y, 0.95f, TextMaxWidth, 2.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("PREMONITION > %s"), *GameMode->GetCurrentPremonition()), PhosphorDim, X, Y, 0.9f, TextMaxWidth, 2.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("DIRECTIVE   > %s"), *GameMode->GetCurrentDirective()), PhosphorDim, X, Y, 0.9f, TextMaxWidth, 10.0f);

    DrawClippedWrappedBlock(FString::Printf(TEXT("ROOM      | %s"), *GameMode->GetCurrentRoomName()), PhosphorPrimary, X, Y, 1.0f, TextMaxWidth, 2.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("STATUS    | %s"), *GameMode->GetCurrentRoomDescription()), PhosphorDim, X, Y, 0.9f, TextMaxWidth, 10.0f);

    DrawClippedWrappedBlock(FString::Printf(TEXT("FOCUS     | %s"), *GameMode->GetSelectedObjectName()), PhosphorSecondary, X, Y, 0.95f, TextMaxWidth, 1.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("EXIT      | %s"), *GameMode->GetSelectedExitLabel()), PhosphorSecondary, X, Y, 0.95f, TextMaxWidth, 1.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("TASK      | %s"), *GameMode->GetSelectedTaskPrompt()), PhosphorSecondary, X, Y, 0.95f, TextMaxWidth, 1.0f);
    DrawClippedWrappedBlock(FString::Printf(TEXT("INSPECT   | %s"), *GameMode->GetLastInspectionText()), PhosphorDim, X, Y, 0.9f, TextMaxWidth, 6.0f);

    DrawClippedWrappedBlock(FString::Printf(TEXT("LOOP NOTE | %s"), *GameMode->GetLastLoopReview()), PhosphorDim, X, Y, 0.85f, TextMaxWidth, 8.0f);

    DrawClippedWrappedBlock(TEXT("KBM  Q/E obj  R/T exit  Z/C task  Tab inspect  F report  X task  Enter use  Shift sprint"), PhosphorDim, X, Y, 0.8f, TextMaxWidth, 1.0f);
    DrawClippedWrappedBlock(TEXT("PAD  LB/RB obj  DPad L/R exit  DPad U/D task  Y inspect  RT report  X task  A use  L3 sprint"), PhosphorDim, X, Y, 0.8f, TextMaxWidth, 8.0f);

    DrawClippedWrappedBlock(TEXT("INTERNAL MONOLOGUE // LIVE BUFFER"), PhosphorPrimary, X, Y, 0.9f, TextMaxWidth, 2.0f);

    const float LogScale = 0.85f;
    const float LogAdvance = 18.0f * LogScale;
    TArray<FString> WrappedLogLines;
    const TArray<FString>& LogLines = GameMode->GetLogLines();
    for (const FString& Line : LogLines)
    {
        const TArray<FString> Wrapped = WrapTextToWidth(Line, LogScale, TextMaxWidth);
        WrappedLogLines.Append(Wrapped);
    }

    const float AvailableLogSpace = FMath::Max(0.0f, ContentBottomY - Y);
    const int32 VisibleLogLineCount = FMath::Max(0, FMath::FloorToInt(AvailableLogSpace / LogAdvance));
    const int32 StartLineIndex = FMath::Max(0, WrappedLogLines.Num() - VisibleLogLineCount);
    for (int32 LineIndex = StartLineIndex; LineIndex < WrappedLogLines.Num(); ++LineIndex)
    {
        if (Y + LogAdvance > ContentBottomY)
        {
            break;
        }

        DrawPhosphorText(WrappedLogLines[LineIndex], PhosphorSecondary, X, Y, LogScale);
        Y += LogAdvance;
    }

    if (GameMode->HasEnded())
    {
        const bool bLost = GameMode->HasLost();
        const FString Headline = GameMode->GetEndingHeadline().IsEmpty()
            ? (bLost ? TEXT("Failure") : TEXT("Outcome"))
            : GameMode->GetEndingHeadline();
        const FString Body = GameMode->GetEndingBody().IsEmpty()
            ? TEXT("The loop has concluded.")
            : GameMode->GetEndingBody();

        const float CenterX = Canvas->ClipX * 0.5f - 280.0f;
        const float CenterY = Canvas->ClipY * 0.76f;
        DrawText(Headline, bLost ? FLinearColor(1.0f, 0.55f, 0.55f) : FLinearColor(1.0f, 0.95f, 0.7f), CenterX, CenterY, Font, 1.3f);
        DrawText(Body, FLinearColor(0.92f, 0.92f, 0.92f), CenterX, CenterY + 28.0f, Font, 0.95f);
    }
}
