#include "fut/ui/clientcli.h"

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
