#ifndef FUTURAMA_FUT_INFRA_CLIHELPERS_H_INCLUDED
#define FUTURAMA_FUT_INFRA_CLIHELPERS_H_INCLUDED

#include <iostream>
#include <stdlib.h>

namespace fut::infra
{
inline void ClearCli()
{
#ifdef _WIN32
    system("cls");
#else
    for (unsigned int i = 0; i < 100; ++i)
    {
        std::cout << '\n';
    }
#endif // #ifdef _WIN32
}
} // namespace fut::infra

#endif // #ifndef FUTURAMA_FUT_INFRA_CLIHELPERS_H_INCLUDED
