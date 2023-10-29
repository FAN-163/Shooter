// Educational project for the online university course OTUS: Unreal Engine Game
// Developer. Professional

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SBaseCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class USpringArmComponent;
class UInputMappingContext;

UCLASS()
class SHOOTER_API ASBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASBaseCharacter();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterInput")
    TObjectPtr<UInputAction> MoveInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterInput")
    TObjectPtr<UInputAction> LookInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterInput")
    TObjectPtr<UInputAction> JumpInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterInput")
    TObjectPtr<UInputAction> RunInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterInput")
    TObjectPtr<UInputMappingContext> InputMapping;

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

private:
   
    void SetupInput();
    void OnMoveAction(const FInputActionValue& Value);
    void OnLookAction(const FInputActionValue& Value);
};
