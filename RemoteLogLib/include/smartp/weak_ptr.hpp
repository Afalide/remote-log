
#ifndef SMART_PTRS_WEAK_PTR_H
#define SMART_PTRS_WEAK_PTR_H

#include <sstream>
#include "smartp/ref_counter.hpp"
#include "smartp/smart_ptr.hpp"

template <typename T>
class smart_pointer;

template <typename T>
class weak_pointer
{

    friend class tests;

    T* _ptr;
    ref_counter* _counter;

public:

    weak_pointer()
        :_ptr(NULL), _counter(NULL)
    {
        std::cout << "weak_pointer ctor ()" << std::endl;
        _counter = new ref_counter();
        _counter->add_weak_ref();
        print();
    }

    weak_pointer(const weak_pointer& other)
        :_ptr(other._ptr), _counter(other._counter)
    {
        std::cout << "weak_pointer ctor (weak_pointer&)" << std::endl;
        _counter->add_weak_ref();
        print();
    }

    weak_pointer(const smart_pointer<T>& sptr)
        :_ptr(sptr._ptr), _counter(sptr._counter)
    {
        std::cout << "weak_pointer ctor (smart_pointer&)" << std::endl;
        _counter->add_weak_ref();
        print();
    }

    ~weak_pointer()
    {
        std::cout << "weak_pointer destructor" << std::endl;
        _counter->remove_weak_ref();
        print();
        delete_counter_if_last();
    }

    smart_pointer<T>
    expose()
    {
        if(0 == _counter->_count)
            return smart_pointer<T>(NULL);

        smart_pointer<T> ret(_ptr);
        delete ret._counter;

        ret._counter = this->_counter;
        ret._counter->add_ref();
        return ret;
    }

    void
    print()
    {
        std::cout << "  "  << describe() << std::endl;
    }

    //the weak pointer never deletes the referee ptr.
    //however it may delete the counter, if it is no
    //longer used:
    //do nothing if weak ref != 0
    //do nothing if strong ref != 0
    //delete the counter if weak ref is 0

    void delete_counter_if_last()
    {
        std::cout << "weak_pointer dcil" << std::endl;
        print();

        if(NULL == _counter)
        {
            std::cout << "  weak check refused (null counter)" << std::endl;
            return;
        }

        if(0 == _counter->_count)
        {
            if(0 == _counter->_weak_count)
            {
                std::cout << "  weak check accepted (deleting counter)" << std::endl;
                delete _counter;
                _counter = NULL;
                return;
            }
            else
            {
                std::cout << "  weak check refused (" << _counter->_weak_count
                << " weak refs remaining)" << std::endl;
            }
        }
        else
        {
            std::cout << "  weak check refused (" << _counter->_count
            << " strong refs remaining)" << std::endl;
        }
    }

    std::string
    describe()
    {
        std::stringstream str;
        str << "weakp at " << this << " refs " << _ptr
            << " [" << _counter->_count << " sr] ["
            << _counter->_weak_count << " wr]";
        return str.str();
    }

};

#endif // SMART_PTRS_WEAK_PTR_H

