#ifndef UNRELATED_OBJECTS_WITH_COMMON_INTERFACE_H
#define UNRELATED_OBJECTS_WITH_COMMON_INTERFACE_H

#include <iostream>

class A {
public:
	void operator()() const { std::cout << "A::operator()\n"; }
};

class B {
public:
	void operator()() const { std::cout << "B::operator()\n"; }
};

#endif