
#pragma once

#include "rlog/commons.hpp"
#include <cassert>

RLOG_NAMESPACE_BEGIN

template <typename T>
class singleton
{
    public:

    singleton();
    virtual ~singleton();

    static T* get_instance();
    //static void delete_instance();

    protected:

    static T* _instance;
};

template <typename T>
singleton<T>::singleton()
{
    assert(nullptr == _instance);
    _instance = static_cast<T*>(this);
}

template <typename T>
singleton<T>::~singleton()
{
    assert(nullptr != _instance);
    _instance = nullptr;
}

template <typename T>
T*
singleton<T>::get_instance()
{
    return _instance;
}

template <typename T> T* singleton<T>::_instance = nullptr;

RLOG_NAMESPACE_END

