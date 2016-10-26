//
// Created by michal on 10/22/16.
//
#include <cstddef> //todo wtf?
#include <iostream>

#include "strdeque.h"
#include "strdequeconst.h"

#ifndef NDEBUG
static const bool debug() {
  return false;
}
#else
static const bool debug() {
  return true;
}
#endif

static std::ostream& write_to_cerr() {
  static std::ios_base::Init init;
  return std::cerr;
}

static void write_error(std::string message) {
  if (debug()) {
    write_to_cerr() << message << "\n";
  }
}

unsigned long &emptystrdeque_id() {
    static unsigned long id = 0;
    return id;
}

static bool &emptystrdeque_initialized() {
    static bool initialized = false;
    return initialized;
}

unsigned long emptystrdeque() {
    write_error("emptystrdeque()");

    if (!emptystrdeque_initialized()) {
        emptystrdeque_initialized() = true;
        emptystrdeque_id() = strdeque_new();
    }

    return emptystrdeque_id();
}
