#include "tests.h"

void test_nested_blocks()
{
	SharedPtr<Resource> p1{ new Resource };
	std::cout << p1.use_count() << " SharedPtr are referencing " << *p1 << "\n";

	// first nested block
	{
		// p2 copy-constructed from p1
		auto p2 = p1;
		std::cout << p1.use_count() << " SharedPtr are referencing " << *p1 << "\n";

		// second nested block
		{
			// p3 copy-constructed from p2
			auto p3 = p2;
			std::cout << p1.use_count() << " SharedPtr are referencing " << *p1 << "\n";

		} // p3 goes out of scope

		std::cout << p1.use_count() << " SharedPtr are referencing " << *p1 << "\n";

	} // p2 goes out of scope

	std::cout << p1.use_count() << " are referencing " << *p1 << "\n";

} // p1 goes out of scope here --> Resource released

/*
Resource (n=1) acquired
1 SharedPtr are referencing a Resource(n=1)
SharedPtr copy-ctor called.
2 SharedPtr are referencing a Resource(n=1)
SharedPtr copy-ctor called.
3 SharedPtr are referencing a Resource(n=1)
~SharedPtr destructor called.
2 SharedPtr are referencing a Resource(n=1)
~SharedPtr destructor called.
1 are referencing a Resource(n=1)
~SharedPtr destructor called.
Resource (n=1) destroyed.
*/

void test_resource_reassignment()
{
	// Resource referenced by p_res
	SharedPtr<Resource> p_res{ new Resource };
	std::cout << "p_res says: " << p_res.use_count() << " SharedPtr are referencing " << *p_res << "\n";

	// Resource referenced by p_other_res independently
	SharedPtr<Resource> p_other_res{ new Resource(-1) };
	std::cout << "p_other_res says: " << p_other_res.use_count() << " SharedPtr are referencing " << *p_other_res << "\n";

	// make p_other_res another reference of Resource, in addition to p_res
	p_other_res = p_res;

	std::cout << "p_res (p_other_res) says: " << p_res.use_count() << "(" << p_other_res.use_count() << ") SharedPtr are referencing " << *p_res << "(" << *p_other_res << ")\n";
}

/*
Resource (n=1) acquired
p_res says: 1 SharedPtr are referencing a Resource(n=1)
Resource (n=-1) acquired
p_other_res says: 1 SharedPtr are referencing a Resource(n=-1)
SharedPtr assignment operator= called.
Resource (n=-1) destroyed.
p_res (p_other_res) says: 2(2) SharedPtr are referencing a Resource(n=1)(a Resource(n=1))
~SharedPtr destructor called.
~SharedPtr destructor called.
Resource (n=1) destroyed.
*/
