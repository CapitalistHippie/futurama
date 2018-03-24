#include "fut/ui/statehandlergameend.h"

#include <functional>

#include <fut/domain/models/gamestate.h>
#include <fut/infra/clihelpers.h>

#include "fut/ui/statehandlermenu.h"

using namespace fut::ui;

void StateHandlerGameEnd::ExitStateBase() noexcept
{
}

void StateHandlerGameEnd::MenuCommandHandler() const
{
    client->ResetGame();

    context->SetStateHandler<StateHandlerMenu>();
}

void StateHandlerGameEnd::PrintCli() const
{
    infra::ClearCli();

    auto gameState = client->GetGame().GetData().gameState;

    if (gameState == domain::models::GameState::Win)
    {
        *outputStream << "You won the game!\n\n";
    }
    else if (gameState == domain::models::GameState::Lose)
    {
        *outputStream << "You lost the game. Better luck next time!\n\n";
    }

    *outputStream << "Available commands.\n"
                  << "menu\t\t\t-- Go back to the menu.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";
}

void StateHandlerGameEnd::EnterState()
{
    RegisterCommandObserver("menu", std::bind(&StateHandlerGameEnd::MenuCommandHandler, this));

    PrintCli();
}
