#include <iostream>
#include <vector>

#include "TypeErasure_using_Inheritance.h"

class A {
public:
	void operator()() const { std::cout << "A::operator()\n"; }
};

class B {
public:
	void operator()() const { std::cout << "B::operator()\n"; }
};

int main() {

	// original (unrelated) types - both implement operator()
	A a;
	B b;

	// type-erased types
	Object typeErasedObjA(a);
	Object typeErasedObjB(b);

	// polymorhic behavior
	typeErasedObjA(); // calling A::operator()
	typeErasedObjB(); // calling B::operator()

	// heterogeneous containers
	std::vector<Object> hetero_vec;
	
	hetero_vec.push_back(a);
	hetero_vec.push_back(b);

	for (const auto& obj : hetero_vec)
	{
		obj(); // calls first A::operator() and then B::operator()
	}
	
	return 0;

}