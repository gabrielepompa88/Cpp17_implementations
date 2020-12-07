#include "tests.h"
#include "UnrelatedObjectsWithCommonInterface.h"
#include "TypeErasure_using_Inheritance.h"

#include <vector>
#include <functional>

void test_type_erasure_inheritance() {

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
}

/* Output:

A::operator()
B::operator()
A::operator()
B::operator()

*/

void test_type_erasure_std_function() {
	// original (unrelated) types - both implement operator()
	A a;
	B b;

	// type-erased types using a std::functions accepting functions (as well functors) 
	// overloading operator()
	std::function<void()> typeErasedObjA(a);
	std::function<void()> typeErasedObjB(b);

	// polymorhic behavior
	typeErasedObjA(); // calling A::operator()
	typeErasedObjB(); // calling B::operator()

	// heterogeneous containers
	std::vector<std::function<void()>> hetero_vec;

	hetero_vec.push_back(a);
	hetero_vec.push_back(b);

	for (const auto& obj : hetero_vec)
	{
		obj(); // calls first A::operator() and then B::operator()
	}
}

/* Output:

A::operator()
B::operator()
A::operator()
B::operator()

*/
