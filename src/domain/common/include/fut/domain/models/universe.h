#ifndef FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED

#include "fut/domain/models/scan.h"
#include "fut/domain/models/sector.h"

namespace fut::domain::models
{
struct Universe
{
    Scan scan;
    Sector* sectors[Scan::ColumnCount][Scan::RowCount];

    Universe()
    {
        for (unsigned int i = 0; i < Scan::ColumnCount; ++i)
        {
            for (unsigned int ii = 0; ii < Scan::RowCount; ++ii)
            {
                sectors[i][ii] = nullptr;
            }
        }
    }

    ~Universe()
    {
        for (unsigned int i = 0; i < Scan::ColumnCount; ++i)
        {
            for (unsigned int ii = 0; ii < Scan::RowCount; ++ii)
            {
                if (sectors[i][ii] != nullptr)
                {
                    delete sectors[i][ii];
                }
            }
        }
    }
}; // struct Universe
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_UNIVERSE_H_INCLUDED
