// Educational project for the online university course OTUS: Unreal Engine Game
// Developer. Professional

#include "Player/SBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASBaseCharacter::ASBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComp);
}

void ASBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    SetupInput();
}

void ASBaseCharacter::SetupInput()
{
    if (auto* PC = Cast<APlayerController>(Controller))
    {
        if (auto* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            InputSystem->AddMappingContext(InputMapping, 0);
        }
    }
}

void ASBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

    if (Input)
    {
        Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ASBaseCharacter::OnMoveAction);
        Input->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ASBaseCharacter::OnLookAction);

        Input->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ASBaseCharacter::Jump);
        Input->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ASBaseCharacter::StopJumping);
    }
}

float ASBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngelBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngelBetween);

    return  CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASBaseCharacter::OnMoveAction(const FInputActionValue& Value)
{
    const FVector2D InputValue = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddMovementInput(GetActorForwardVector(), InputValue.Y);
        AddMovementInput(GetActorRightVector(), InputValue.X);
    }
}

void ASBaseCharacter::OnLookAction(const FInputActionValue& Value)
{
    const FVector2D InputValue = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerPitchInput(InputValue.Y);
        AddControllerYawInput(InputValue.X);
    }
}

void ASBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
