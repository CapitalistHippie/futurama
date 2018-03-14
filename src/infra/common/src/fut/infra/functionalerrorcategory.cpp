#include "fut/infra/functionalerrorcategory.h"

using namespace fut;
using namespace fut::infra;

const char* FunctionalErrorCategory::name() const noexcept
{
    return "Futurama Infra Functional Error Category";
}

std::string FunctionalErrorCategory::message(int ev) const
{
    return "";
}

const std::error_category& fut::infra::GetFunctionalErrorCategory()
{
    static FunctionalErrorCategory instance;
    return instance;
}

std::error_code std::make_error_code(FunctionalError error)
{
    return std::error_code(static_cast<int>(error), fut::infra::GetFunctionalErrorCategory());
}
