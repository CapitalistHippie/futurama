#include "fut/ui/clientcli.h"

#include <functional>
#include <system_error>

#include <fut/domain/events/statechanged.h>
#include <fut/domain/models/gamestate.h>

#include "fut/ui/command.h"
#include "fut/ui/statehandlergameend.h"
#include "fut/ui/statehandlermenu.h"

using namespace fut;
using namespace fut::ui;

void ClientCli::SetStateHandler(StateHandler* stateHandler)
{
    if (activeStateHandler != nullptr)
    {
        activeStateHandler->ExitState();
        delete activeStateHandler;
    }

    activeStateHandler = stateHandler;

    if (activeStateHandler != nullptr)
    {
        activeStateHandler->EnterState();
    }
}

ClientCli::ClientCli(app::Client& client, std::istream& inputStream, std::ostream& outputStream)
  : client(&client)
  , inputStream(&inputStream)
  , outputStream(&outputStream)
  , isRunning(false)
  , shouldStop(false)
  , activeStateHandler(nullptr)
{
}

ClientCli::~ClientCli() noexcept
{
    if (activeStateHandler != nullptr)
    {
        delete activeStateHandler;
    }
}

void ClientCli::Start()
{
    if (IsRunning())
    {
        return;
    }

    isRunning = true;

    auto stopCommandHandler = std::bind(&ClientCli::Stop, this);

    commandsSubject.RegisterPredicateObserver<Command>(
      [](const Command& command) { return strcmp(command.name, "quit") == 0; }, stopCommandHandler);
    commandsSubject.RegisterPredicateObserver<Command>(
      [](const Command& command) { return strcmp(command.name, "exit") == 0; }, stopCommandHandler);
    commandsSubject.RegisterPredicateObserver<Command>(
      [](const Command& command) { return strcmp(command.name, "stop") == 0; }, stopCommandHandler);

    client->GetGameEventsSubject().RegisterPredicateObserver<domain::events::StateChanged>(
      [](const domain::events::StateChanged& evt) {
          return evt.newState == domain::models::GameState::Win || evt.newState == domain::models::GameState::Lose;
      },
      std::bind(&ClientCli::SetStateHandler<StateHandlerGameEnd>, this));

    SetStateHandler<StateHandlerMenu>();

    do
    {
        auto command = commandParser.ParseCommand(*inputStream);
        commandsSubject.NotifyObservers(command);
    } while (!shouldStop);

    // Cleanup should be done here.
    commandsSubject.Clear();
    client->GetGameEventsSubject().Clear();

    isRunning = false;
    shouldStop = false;
}

void ClientCli::Stop()
{
    if (!IsRunning())
    {
        return;
    }

    shouldStop = true;
}

bool ClientCli::IsRunning() const
{
    return isRunning;
}
