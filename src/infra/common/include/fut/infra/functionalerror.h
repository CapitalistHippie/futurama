#ifndef FUTURAMA_FUT_INFRA_FUNCTIONALERROR_H_INCLUDED
#define FUTURAMA_FUT_INFRA_FUNCTIONALERROR_H_INCLUDED

namespace fut::infra
{
enum class FunctionalError
{
    None,
    OutOfSpace,
    CliCommandNotRegistered,
    CliCommandInvalidParameterInputType,
    UnableToOpenFile,
    NoFileOpened
}; // enum class FunctionalError
} // namespace fut::infra

#endif // #ifndef FUTURAMA_FUT_INFRA_FUNCTIONALERROR_H_INCLUDED
