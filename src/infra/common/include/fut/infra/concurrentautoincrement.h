#ifndef FUTURAMA_FUT_INFRA_CONCURRENTAUTOINCREMENT_H_INCLUDED
#define FUTURAMA_FUT_INFRA_CONCURRENTAUTOINCREMENT_H_INCLUDED

#include <atomic>

namespace fut::infra
{
template<typename T>
class ConcurrentAutoIncrement
{
  private:
    static std::atomic<T> autoIncrement;

    T increment;

  public:
    ConcurrentAutoIncrement()
      : increment(autoIncrement++)
    {
    }

    operator T() const noexcept
    {
        return increment;
    }

    bool operator==(T other) const noexcept
    {
        return increment == other;
    }
}; // class ConcurrentAutoIncrement

template<typename T>
std::atomic<T> ConcurrentAutoIncrement<T>::autoIncrement;
} // namespace fut::infra

#endif // #ifndef FUTURAMA_FUT_INFRA_CONCURRENTAUTOINCREMENT_H_INCLUDED
