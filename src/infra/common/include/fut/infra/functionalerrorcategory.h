#ifndef FUTURAMA_FUT_INFRA_FUNCTIONALERRORCATEGORY_H_INCLUDED
#define FUTURAMA_FUT_INFRA_FUNCTIONALERRORCATEGORY_H_INCLUDED

#include <system_error>

#include "fut/infra/functionalerror.h"

namespace fut::infra
{
class FunctionalErrorCategory : public std::error_category
{
  public:
    virtual const char* name() const noexcept;
    virtual std::string message(int ev) const;
}; // class FunctionalErrorCategory

const std::error_category& GetFunctionalErrorCategory();
} // namespace fut::infra

namespace std
{
template<>
struct is_error_code_enum<fut::infra::FunctionalError> : true_type
{
};

error_code make_error_code(fut::infra::FunctionalError);
} // namespace std

#endif // #ifndef FUTURAMA_FUT_INFRA_FUNCTIONALERRORCATEGORY_H_INCLUDED
