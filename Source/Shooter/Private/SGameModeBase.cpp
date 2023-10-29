// Educational project for the online university course OTUS: Unreal Engine Game
// Developer. Professional

#include "SGameModeBase.h"

#include "Player/SBaseCharacter.h"
#include "Player/SPlayerController.h"

ASGameModeBase::ASGameModeBase()
{
    DefaultPawnClass = ASBaseCharacter::StaticClass();
    PlayerControllerClass = ASPlayerController::StaticClass();
}
