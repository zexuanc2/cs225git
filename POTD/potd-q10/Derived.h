#pragma once
#include <iostream>
#include "Base.h"

class Derived : public Base {
  public:
    string foo();
    virtual string bar();
    virtual ~Derived() {}
};