#include "fut/ui/clientcli.h"

#include <functional>
#include <system_error>

#include "fut/ui/command.h"

using namespace fut;
using namespace fut::ui;

ClientCli::ClientCli(app::Client& client, std::istream& inputStream, std::ostream& outputStream)
  : client(&client)
  , inputStream(&inputStream)
  , outputStream(&outputStream)
  , isRunning(false)
  , shouldStop(false)
{
}

void ClientCli::Start()
{
    if (IsRunning())
    {
        return;
    }

    isRunning = true;

    auto stopCommandHandler = std::bind(&ClientCli::Stop, this);

    commandSubject.RegisterPredicateObserver<Command>(
      [](const Command& command) { return strcmp(command.name, "quit") == 0; }, stopCommandHandler);
    commandSubject.RegisterPredicateObserver<Command>(
      [](const Command& command) { return strcmp(command.name, "exit") == 0; }, stopCommandHandler);
    commandSubject.RegisterPredicateObserver<Command>(
      [](const Command& command) { return strcmp(command.name, "stop") == 0; }, stopCommandHandler);

    client->StartGame();

    do
    {
        try
        {
            auto command = commandParser.ParseCommand(*inputStream);
            commandSubject.NotifyObservers(command);
        }
        catch (const std::system_error& e)
        {
            // if (e.code() == infra::FunctionalError::CommandNotRegistered)
            //{
            //    *outputStream << "Unavailable or unknown command. Please try something else!\n\n";
            //}
            // else if (e.code() == infra::FunctionalError::CommandInvalidParameterInputType)
            //{
            //    *outputStream << "Invalid parameter(s). Please try something else!\n\n";
            //}
            // else
            //{
            //    throw;
            //}
        }
    } while (!shouldStop);

    // Cleanup should be done here.
    commandSubject.Clear();

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
