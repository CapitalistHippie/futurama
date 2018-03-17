#ifndef FUTURAMA_FUT_APP_FUTURAMAAPPEXCEPTION_H_INCLUDED
#define FUTURAMA_FUT_APP_FUTURAMAAPPEXCEPTION_H_INCLUDED

#include <fut/infra/futuramaexception.h>

#include "fut/app/errorcode.h"

namespace fut::app
{
class FuturamaAppException : infra::FuturamaException
{
  public:
    ErrorCode errorCode;

    FuturamaAppException(ErrorCode errorCode) noexcept
      : errorCode(errorCode)
    {
    }
}; // class FuturamaAppException
} // namespace fut::app

#endif // #ifndef FUTURAMA_FUT_APP_FUTURAMAAPPEXCEPTION_H_INCLUDED
