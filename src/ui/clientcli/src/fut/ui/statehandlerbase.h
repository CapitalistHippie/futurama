#ifndef FUTURAMA_FUT_UI_STATEHANDLERBASE_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLERBASE_H_INCLUDED

#include <ostream>

#include <fut/app/client.h>
#include <fut/infra/subject.h>

#include "fut/ui/clientcli.h"
#include "fut/ui/statehandler.h"

namespace fut::ui
{
class StateHandlerBase : public StateHandler
{
  protected:
    ClientCli* context;
    app::Client* client;
    infra::Subject* commandSubject;
    std::ostream* outputStream;

  public:
    StateHandlerBase(ClientCli& context,
                     app::Client& client,
                     infra::Subject& commandSubject,
                     std::ostream& outputStream);
    ~StateHandlerBase() noexcept = default;

    virtual void ExitStateBase() noexcept = 0;

    void ExitState() noexcept override;
}; // class StateHandlerBase
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLERBASE_H_INCLUDED
