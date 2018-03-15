#ifndef FUTURAMA_FUT_UI_CLIENTCLI_H_INCLUDED
#define FUTURAMA_FUT_UI_CLIENTCLI_H_INCLUDED

#include <istream>
#include <ostream>

#include <fut/app/client.h>
#include <fut/infra/subject.h>

#include "fut/ui/commandparser.h"
#include "fut/ui/statehandler.h"

namespace fut::ui
{
class ClientCli
{
  private:
    app::Client* client;

    std::istream* inputStream;
    std::ostream* outputStream;

    bool isRunning;
    bool shouldStop;

    CommandParser commandParser;
    infra::Subject commandsSubject;

    StateHandler* activeStateHandler;

    void SetStateHandler(StateHandler* stateHandler);

  public:
    ClientCli(app::Client& client, std::istream& inputStream, std::ostream& outputStream);
    ~ClientCli() noexcept;

    template<typename TStateHandler>
    void SetStateHandler()
    {
        TStateHandler* stateHandler = new TStateHandler(*this, *client, commandsSubject, *outputStream);

        try
        {
            SetStateHandler(stateHandler);
        }
        catch (...)
        {
            delete stateHandler;

            throw;
        }
    }

    void Start();
    void Stop();

    bool IsRunning() const;
}; // class ClientCli
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_CLIENTCLI_H_INCLUDED
