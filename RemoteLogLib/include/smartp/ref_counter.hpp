
#ifndef SMART_PTRS_REF_COUNTER_H
#define SMART_PTRS_REF_COUNTER_H

#include <iostream>

class ref_counter
{
    template <typename T> friend class smart_pointer;
    template <typename T> friend class weak_pointer;
    friend class tests;

    int _count;
    int _weak_count;

public:

    ref_counter();
    ~ref_counter();

    void add_ref();
    void remove_ref();
    void add_weak_ref();
    void remove_weak_ref();
};

#endif // SMART_PTRS_REF_COUNTER_H

