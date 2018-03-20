#include "fut/ui/statehandlerontheway.h"

#include <functional>

#include <fut/app/errorcode.h>
#include <fut/app/futuramaappexception.h>
#include <fut/domain/events/movedtofield.h>
#include <fut/domain/events/movedtoheadquarters.h>
#include <fut/domain/events/movedtosector.h>
#include <fut/domain/events/packagepickedup.h>
#include <fut/infra/clihelpers.h>

#include "fut/ui/statehandlerheadquarters.h"

using namespace fut::ui;

void StateHandlerOnTheWay::ExitStateBase() noexcept
{
}

void fut::ui::StateHandlerOnTheWay::MoveCommandHandler(const Command& command) const
{
    if (command.argumentCount < 1)
    {
        PrintCli("Too few arguments.");
        return;
    }

    try
    {
        if (strcmp(command.arguments[0], "up") == 0)
        {
            client->MoveUp();
        }
        else if (strcmp(command.arguments[0], "right") == 0)
        {
            client->MoveRight();
        }
        else if (strcmp(command.arguments[0], "down") == 0)
        {
            client->MoveDown();
        }
        else if (strcmp(command.arguments[0], "left") == 0)
        {
            client->MoveLeft();
        }
        else
        {
            PrintCli("Invalid direction.");
            return;
        }
    }
    catch (app::FuturamaAppException exception)
    {
        if (exception.errorCode == app::ErrorCode::FieldTaken)
        {
            PrintCli("The field you're moving to is already taken by something else.");
            return;
        }

        throw;
    }
}

void StateHandlerOnTheWay::PickupCommandHandler() const
{
    if (client->GetGame().HavePackage())
    {
        PrintCli("You already have a package.");
        return;
    }

    if (!client->GetGame().IsShipNextToThing(domain::models::SectorFieldThing::Planet))
    {
        PrintCli("You have to be next to a planet to pickup a package.");
        return;
    }

    if (!client->GetGame().CanPickupPackage())
    {
        PrintCli("You can not pick up a package right now.");
        return;
    }

    client->PickupPackage();
}

void StateHandlerOnTheWay::ExamineCommandHandler() const
{
    if (!client->GetGame().HavePackage())
    {
        PrintCli("You don't have a package.");
    }

    PrintCliWithPackageInfo();
}

void StateHandlerOnTheWay::DeliverCommandHandler() const
{
    if (!client->GetGame().HavePackage())
    {
        PrintCli("You don't have a package.");
    }

    if (!client->GetGame().IsShipNextToThing(domain::models::SectorFieldThing::Planet))
    {
        PrintCli("You have to be next to a planet to deliver a package.");
        return;
    }

    client->DeliverPackage();
}

void StateHandlerOnTheWay::SkipCommandHandler() const
{
    client->SkipTurn();
}

void StateHandlerOnTheWay::MovedToSectorGameEventHandler() const
{
    PrintCli();
}

void StateHandlerOnTheWay::MovedToFieldGameEventHandler() const
{
    PrintCli();
}

void StateHandlerOnTheWay::MovedToHeadquartersGameEventHandler() const
{
    context->SetStateHandler<StateHandlerHeadquarters>();
}

void StateHandlerOnTheWay::PackagePickedUpGameEventHandler() const
{
    PrintCliWithPackageInfo();
}

void StateHandlerOnTheWay::PrintCliWithPackageInfo() const
{
    PrintCli();
    PrintPackageInfo();

    *outputStream << "\n\n";
}

void StateHandlerOnTheWay::PrintCli(const char* extra) const
{
    infra::ClearCli();
    *outputStream << "You're on the route route to deliver your package. Navigate to the planet you need to deliver "
                     "your package to.\n\n";

    PrintSector();

    *outputStream << "\n\n";

    *outputStream << "Available commands.\n"
                  << "move <direction>\t-- Move to the field up, right, down or left of you.\n"
                  << "pickup\t\t\t-- Pickup a package from the planet next to you.\n"
                  << "examine\t\t\t-- Shows the package contents and destination.\n"
                  << "deliver\t\t\t-- Deliver the package to the planet next to you.\n"
                  << "skip\t\t\t-- Skip this turn.\n"
                  << "quit/exit/stop\t\t-- Quit the game.\n\n";

    if (extra != nullptr)
    {
        *outputStream << extra << "\n\n";
    }
}

void StateHandlerOnTheWay::PrintSector() const
{
    const auto& sector = client->GetGame().GetCurrentSector();
    const auto& ship = client->GetGame().GetData().ship;

    for (unsigned int i = 0; i < sector.RowCount; ++i)
    {
        *outputStream << ' ';

        for (unsigned int ii = 0; ii < sector.ColumnCount; ++ii)
        {
            if (ship.fieldPoint.y == i && ship.fieldPoint.x == ii)
            {
                *outputStream << "P ";

                continue;
            }

            const auto& field = sector.fields[ii][i];

            switch (field.thing)
            {
                case domain::models::SectorFieldThing::Empty:
                    *outputStream << char(250) << ' ';
                    break;
                case domain::models::SectorFieldThing::Asteroid:
                    *outputStream << "O ";
                    break;
                case domain::models::SectorFieldThing::Meeting:
                    *outputStream << "* ";
                    break;
                case domain::models::SectorFieldThing::Planet:
                    *outputStream << "@ ";
                    break;
            }
        }

        if (i != sector.RowCount - 1)
        {
            *outputStream << '\n';
        }
    }
}

void fut::ui::StateHandlerOnTheWay::PrintPackageInfo() const
{
    const domain::models::Package& package = *client->GetGame().GetData().ship.package;

    *outputStream << "Package contents description: " << package.contentsDescription << "\n";
    *outputStream << "Package destination description: " << package.destinationDescription << "\n";
    *outputStream << "Package destination: Sector (" << package.destinationSectorPoint.x << ','
                  << package.destinationSectorPoint.y << ") - Planet (" << package.destinationFieldPoint.x << ','
                  << package.destinationFieldPoint.y << ")";
}

void StateHandlerOnTheWay::EnterState()
{
    RegisterCommandObserver("move", std::bind(&StateHandlerOnTheWay::MoveCommandHandler, this, std::placeholders::_1));
    RegisterCommandObserver("pickup", std::bind(&StateHandlerOnTheWay::PickupCommandHandler, this));
    RegisterCommandObserver("examine", std::bind(&StateHandlerOnTheWay::ExamineCommandHandler, this));
    RegisterCommandObserver("deliver", std::bind(&StateHandlerOnTheWay::DeliverCommandHandler, this));
    RegisterCommandObserver("skip", std::bind(&StateHandlerOnTheWay::SkipCommandHandler, this));

    RegisterGameEventObserver<domain::events::MovedToSector>(
      std::bind(&StateHandlerOnTheWay::MovedToSectorGameEventHandler, this));

    RegisterGameEventObserver<domain::events::MovedToField>(
      std::bind(&StateHandlerOnTheWay::MovedToFieldGameEventHandler, this));

    RegisterGameEventObserver<domain::events::MovedToHeadquarters>(
      std::bind(&StateHandlerOnTheWay::MovedToHeadquartersGameEventHandler, this));

    RegisterGameEventObserver<domain::events::PackagePickedUp>(
      std::bind(&StateHandlerOnTheWay::PackagePickedUpGameEventHandler, this));

    PrintCli();
}
