//
// Created by michal on 10/22/16.
//
#include <cstddef> //todo wtf?

#include "strdeque.h"
#include "strdequeconst.h"

unsigned long& emptystrdeque_id()
{
    static unsigned long id = 0;
    return id;
}

bool& emptystrdeque_initialized()
{
    static bool initialized = false;
    return initialized;
}

unsigned long emptystrdeque() {
    if (!emptystrdeque_initialized()) {
        emptystrdeque_initialized() = true;
        emptystrdeque_id() = strdeque_new();
    }

    return emptystrdeque_id();
}
