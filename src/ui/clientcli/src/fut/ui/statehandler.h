#ifndef FUTURAMA_FUT_UI_STATEHANDLER_H_INCLUDED
#define FUTURAMA_FUT_UI_STATEHANDLER_H_INCLUDED

namespace fut::ui
{
class StateHandler
{
  public:
    ~StateHandler() noexcept = default;

    virtual void EnterState() = 0;
    virtual void ExitState() noexcept = 0;
}; // class StateHandler
} // namespace fut::ui

#endif // FUTURAMA_FUT_UI_STATEHANDLER_H_INCLUDED
