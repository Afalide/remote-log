
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
    //    if(NULL == _instance)
    //        _instance = new T;

    return _instance;
}

//template <typename T>
//void
//singleton<T>::delete_instance()
//{
//    if(NULL == _instance)
//        return;
//
//    delete _instance;
//    _instance = NULL;
//}

RLOG_NAMESPACE_END

