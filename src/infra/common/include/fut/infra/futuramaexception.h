#ifndef FUTURAMA_FUT_INFRA_FUTURAMAEXCEPTION_H_INCLUDED
#define FUTURAMA_FUT_INFRA_FUTURAMAEXCEPTION_H_INCLUDED

#include <exception>

namespace fut::infra
{
class FuturamaException : public std::exception
{
}; // class FuturamaException
} // namespace fut::infra

#endif // #ifndef FUTURAMA_FUT_INFRA_FUTURAMAEXCEPTION_H_INCLUDED
