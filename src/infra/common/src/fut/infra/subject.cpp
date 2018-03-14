#include "fut/infra/subject.h"

using namespace fut::infra;

Subject::Subject()
{
    for (auto& predicateObserversPredicate : predicateObserversPredicates)
    {
        predicateObserversPredicate = nullptr;
    }

    for (auto& predicateObserversobserver : predicateObserversObservers)
    {
        predicateObserversobserver = nullptr;
    }

    for (auto& simpleObserversObserver : simpleObserversObservers)
    {
        simpleObserversObserver = nullptr;
    }
}

Subject::~Subject()
{
    Clear();
}

void Subject::UnregisterPredicateObserver(ObserverHandle handle)
{
    if (predicateObserversPredicates[handle] != nullptr)
    {
        delete predicateObserversPredicates[handle];
        predicateObserversPredicates[handle] = nullptr;
    }

    if (predicateObserversObservers[handle] != nullptr)
    {
        delete predicateObserversObservers[handle];
        predicateObserversObservers[handle] = nullptr;
    }
}

void Subject::UnregisterSimpleObserver(ObserverHandle handle)
{
    if (simpleObserversObservers[handle] != nullptr)
    {
        delete simpleObserversObservers[handle];
        simpleObserversObservers[handle] = nullptr;
    }
}

void Subject::Clear()
{
    for (auto& predicateObserversPredicate : predicateObserversPredicates)
    {
        if (predicateObserversPredicate != nullptr)
        {
            delete predicateObserversPredicate;
            predicateObserversPredicate = nullptr;
        }
    }

    for (auto& predicateObserversobserver : predicateObserversObservers)
    {
        if (predicateObserversobserver != nullptr)
        {
            delete predicateObserversobserver;
            predicateObserversobserver = nullptr;
        }
    }

    for (auto& simpleObserversObserver : simpleObserversObservers)
    {
        if (simpleObserversObserver != nullptr)
        {
            delete simpleObserversObserver;
            simpleObserversObserver = nullptr;
        }
    }
}
