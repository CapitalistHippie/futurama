#ifndef FUTURAMA_FUT_DOMAIN_MODELS_PACKAGE_H_INCLUDED
#define FUTURAMA_FUT_DOMAIN_MODELS_PACKAGE_H_INCLUDED

#include <fut/infra/point.h>

namespace fut::domain::models
{
struct Package
{
    char contentsDescription[64] = "";
    char destinationDescription[64] = "";

    infra::Point destinationSectorPoint;
    infra::Point destinationFieldPoint;
}; // struct Package
} // namespace fut::domain::models

#endif // FUTURAMA_FUT_DOMAIN_MODELS_PACKAGE_H_INCLUDED
