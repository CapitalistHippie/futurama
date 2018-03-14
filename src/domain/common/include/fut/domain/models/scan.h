#ifndef FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED

#include "fut/domain/models/scansector.h"

namespace fut::domain::models
{
struct Scan
{
    static const unsigned int ColumnCount = 5;
    static const unsigned int RowCount = 5;

    ScanSector sectors[ColumnCount][RowCount];
}; // struct Scan
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_SCAN_H_INCLUDED
