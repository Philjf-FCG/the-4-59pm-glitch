#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Glitch459PMPawn.generated.h"

UCLASS()
class GLITCH459PM_API AGlitch459PMPawn : public ACharacter
{
    GENERATED_BODY()

public:
    AGlitch459PMPawn();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#if WITH_DEV_AUTOMATION_TESTS
    void AutomationAttachController(class AController* InController);
    void AutomationMoveForward(float Value);
    void AutomationMoveRight(float Value);
    void AutomationStartSprint();
    void AutomationStopSprint();
    FVector AutomationGetPendingMovementInput() const;
    float AutomationGetMaxWalkSpeed() const;
#endif

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void StartSprint();
    void StopSprint();

    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* FirstPersonCamera;

    UPROPERTY(EditDefaultsOnly)
    float WalkSpeed = 250.0f;

    UPROPERTY(EditDefaultsOnly)
    float SprintSpeed = 450.0f;
};
