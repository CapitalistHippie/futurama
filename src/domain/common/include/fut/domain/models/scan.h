#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED

#include "fut/domain/models/scansector.h"

namespace fut::domain::models
{
struct Scan
{
    ScanSector sectors[5][5];
}; // struct Scan
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED
