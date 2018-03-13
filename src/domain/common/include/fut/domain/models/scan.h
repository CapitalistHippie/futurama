#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED

#include "fut/domain/models/scansector.h"

namespace fut::domain::models
{
template<unsigned int columns, unsigned int rows>
struct Scan
{
    ScanSector sectors[columns][rows];
}; // struct Scan
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED
