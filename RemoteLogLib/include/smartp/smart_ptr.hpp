
#ifndef SMART_PTRS_SMART_PTR_H
#define SMART_PTRS_SMART_PTR_H

#include "ref_counter.hpp"
#include "smartp/weak_ptr.hpp"
#include <sstream>
#include  "rlog/commons.hpp"

template <typename T>
class smart_pointer
{

    friend class tests;
    friend class weak_pointer<T>;

    T* _ptr;
    ref_counter* _counter;

    public:

    //empty ctor

    smart_pointer()
        :_ptr(NULL), _counter(NULL)
    {
        //std::cout << "smart_pointer() " << std::endl;

        _counter = new ref_counter();
        _counter->add_ref();

        //std::cout << "  " << describe() << std::endl;
    }

    //init ctor

    smart_pointer(T* ptr)
        :_ptr(ptr), _counter(NULL)
    {
        //std::cout << "smart_pointer(T* ptr) " << std::endl;

        _counter = new ref_counter();
        _counter->add_ref();

        //std::cout << "  " << describe() << std::endl;
    }

    //copy ctor

    smart_pointer(const smart_pointer<T>& other)
        :_ptr(other._ptr), _counter(other._counter)
    {
        //std::cout << "smart_pointer(smart_pointer&) " << std::endl;

        _counter->add_ref();

        // std::cout << "  " << describe() << std::endl;
    }

    //destructor

    ~smart_pointer()
    {
        // std::cout << "smart_pointer destructor " << std::endl;
        // std::cout << "  " << describe() << std::endl;

        //remove a ref

        _counter->remove_ref();

        //delete the ptr if necessary

        delete_if_last();
    }

    //operator =

    smart_pointer<T>& operator=(const smart_pointer<T>& other)
    {
        // std::cout << "smart_pointer operator= old:" << _ptr << " new:" << other._ptr << std::endl;
        // std::cout << "  " << describe() << std::endl;

        //ignore self affect

        if(this == &other)
            return *this;

        //remove a count, since after this call we loose
        //that current ref

        _counter->remove_ref();
        delete_if_last();

        //assign from other

        _counter = other._counter;
        _counter->add_ref();
        _ptr = other._ptr;

        return *this;
    }

    //operator ->

    T* operator->()
    {
        return _ptr;
    }

    void delete_if_last()
    {
        // std::cout << "smart_pointer dil start (sp at " << this << ")" << std::endl;
        // std::cout << "  " << describe() << std::endl;
        delete_if_last_impl();
        // std::cout << "smart_pointer dil end   (sp at " << this << ")" << std::endl;
    }

    //cleanup:
    //delete the pointer if it has 0 strong refs
    //delete the counter if it has 0 strong refs and 0 weak refs

    void delete_if_last_impl()
    {
        if(0 != _counter->_count)
        {
            // std::cout << "    strong check refused (" << _counter->_count
            //            << " strong refs remaining)" << std::endl;
            // std::cout << "    weak check skipped (strong refs remaining)" << std::endl;
            return;
        }

        if(NULL == _ptr)
        {
            //   std::cout << "    strong check refused (ptr referee is null)" << std::endl;
        }
        else
        {
            //   std::cout << "    strong check accepted (deleting ptr referee)" << std::endl;
            delete _ptr;
            _ptr = NULL;
        }

        if(0 != _counter->_weak_count)
        {
            //  std::cout << "    weak check refused (" << _counter->_weak_count
            //  << " weak refs remaining) " << std::endl;
            return;
        }

        // std::cout << "    weak check accepted (deleting counter) " << std::endl;
        delete _counter;
        _counter = NULL;
    }

    //stop watching the referee ptr:
    //- it won't be deleted when this smartpointer exits the scope.
    //- it becomes a whole new empty smart pointer.
    //- others smartp and weakp refs will see the counter decrease
    //  accordingly.

    T*
        release()
    {
        //*this = smart_pointer<T>();
        T* ret = _ptr;


        _ptr = NULL;
        _counter->remove_ref();

        //if this was the last smartp, also delete the old counter
        //the user is responsible of the referee ptr deletion
        if(0 == _counter->_count && 0 == _counter->_weak_count)
            delete _counter;

        //this smartp will persist, so use a new and separate
        //ref counter
        _counter = new ref_counter();
        _counter->add_ref();
        return ret;
    }

    std::string
        describe()
    {
        std::stringstream str;
        str << "smartp at " << this << " refs " << _ptr
            << " [" << _counter->_count << " sr] ["
            << _counter->_weak_count << " wr]";
        return str.str();
    }

    //global comparison operators

    //compare directly a pointer and a smartpointer

    friend
    bool operator== (void* left, const smart_pointer<T>& right)
    {
        return left == right._ptr;
    }


    friend
    bool operator== (const smart_pointer<T>& left, void* right)
    {
        return left._ptr == right;
    }

    //compare 2 smartpointers

    friend
    bool operator== (smart_pointer<T>& left, const smart_pointer<T>& right)
    {
        return left._ptr == right._ptr;
    }
};



#endif // SMART_PTRS_SMART_PTR_H








