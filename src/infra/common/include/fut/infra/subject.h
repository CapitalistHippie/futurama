#ifndef FUTURAMA_FUT_INFRA_SUBJECT_H_INCLUDED
#define FUTURAMA_FUT_INFRA_SUBJECT_H_INCLUDED

#include <system_error>
#include <typeindex>

#include "fut/infra/concurrentautoincrement.h"
#include "fut/infra/functionalerror.h"
#include "fut/infra/functionalerrorcategory.h"

namespace fut::infra
{
namespace detail
{
class ObservablePredicate
{
  public:
    virtual ~ObservablePredicate() noexcept = default;
    virtual bool Predicate(const void* command) const = 0;
}; // class ObservablePredicate

template<typename TObservable, typename TPredicate>
class ObservablePredicateImpl : public ObservablePredicate
{
  private:
    TPredicate predicate;

  public:
    ObservablePredicateImpl(TPredicate predicate)
      : predicate(predicate)
    {
    }

    bool Predicate(const void* command) const override
    {
        return predicate(*static_cast<const TObservable*>(command));
    }
}; // class ObservablePredicateImpl

class Observer
{
  public:
    virtual ~Observer() noexcept = default;
    virtual bool CanHandleType(std::type_index type) const = 0;
    virtual void Notify(const void* command) const = 0;
}; // class Observer

template<typename TObservable, typename TObserver>
class ObserverImpl : public Observer
{
  private:
    TObserver observer;

  public:
    typedef unsigned int Id;

    infra::ConcurrentAutoIncrement<Id> id;

    ObserverImpl(TObserver observer)
      : observer(observer)
    {
    }

    bool CanHandleType(std::type_index type) const override
    {
        return type == typeid(TObservable);
    }

    void Notify(const void* command) const override
    {
        return observer(*static_cast<const TObservable*>(command));
    }
}; // class ObserverImpl
} // namespace detail

class Subject
{
  public:
    static const unsigned int ObserverCount = 64;

    typedef unsigned int ObserverHandle;

  private:
    detail::ObservablePredicate* predicateObserversPredicates[ObserverCount];
    detail::Observer* predicateObserversObservers[ObserverCount];

    detail::Observer* simpleObserversObservers[ObserverCount];

  public:
    Subject();
    ~Subject();

    template<typename TObservable>
    void NotifyObservers(const TObservable& observable) const
    {
        for (unsigned int i = 0; i < ObserverCount; ++i)
        {
            if (predicateObserversPredicates[i] != nullptr)
            {
                if (!predicateObserversObservers[i]->CanHandleType(typeid(TObservable)))
                {
                    continue;
                }

                if (!predicateObserversPredicates[i]->Predicate(static_cast<const void*>(&observable)))
                {
                    continue;
                }

                predicateObserversObservers[i]->Notify(&observable);
            }

            if (simpleObserversObservers[i] != nullptr)
            {
                if (!simpleObserversObservers[i]->CanHandleType(typeid(TObservable)))
                {
                    continue;
                }

                simpleObserversObservers[i]->Notify(&observable);
            }
        }
    }

    template<typename TObservable, typename TPredicate, typename TObserver>
    ObserverHandle RegisterPredicateObserver(TPredicate predicate, TObserver observer)
    {
        for (unsigned int i = 0; i < ObserverCount; ++i)
        {
            if (predicateObserversPredicates[i] != nullptr)
            {
                continue;
            }

            detail::ObservablePredicate* predicateObj = nullptr;
            detail::Observer* observerObj = nullptr;

            try
            {
                predicateObj = new detail::ObservablePredicateImpl<TObservable, TPredicate>(predicate);
                observerObj = new detail::ObserverImpl<TObservable, TObserver>(observer);

                predicateObserversPredicates[i] = predicateObj;
                predicateObserversObservers[i] = observerObj;

                return i;
            }
            catch (...)
            {
                if (predicateObj == nullptr)
                {
                    delete predicateObj;
                }

                if (observerObj == nullptr)
                {
                    delete observerObj;
                }

                throw;
            }
        }

        throw std::system_error(std::make_error_code(FunctionalError::OutOfSpace));
    }

    template<typename TObservable, typename TObserver>
    ObserverHandle RegisterSimpleObserver(TObserver observer)
    {
        for (unsigned int i = 0; i < ObserverCount; ++i)
        {
            if (simpleObserversObservers[i] != nullptr)
            {
                continue;
            }

            auto observerObj = new detail::ObserverImpl<TObservable, TObserver>(observer);

            try
            {
                simpleObserversObservers[i] = observerObj;

                return i;
            }
            catch (...)
            {
                if (observerObj == nullptr)
                {
                    delete observerObj;
                }

                throw;
            }
        }

        throw std::system_error(std::make_error_code(FunctionalError::OutOfSpace));
    }

    void UnregisterPredicateObserver(ObserverHandle handle);
    void UnregisterSimpleObserver(ObserverHandle handle);

    void Clear();
}; // class Subject
} // namespace fut::infra

#endif // #ifndef FUTURAMA_FUT_INFRA_SUBJECT_H_INCLUDED
