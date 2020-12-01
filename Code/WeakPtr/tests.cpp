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
Resource acquired
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
~Resource(): Resource released.
~ControlBlock(): ControlBlock released.
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
Resource acquired
p_res says: 1 SharedPtr are referencing a Resource(n=1)
Resource acquired
p_other_res says: 1 SharedPtr are referencing a Resource(n=-1)
SharedPtr assignment operator= called.
~Resource(): Resource released.
~ControlBlock(): ControlBlock released.
p_res (p_other_res) says: 2(2) SharedPtr are referencing a Resource(n=1)(a Resource(n=1))
~SharedPtr destructor called.
~SharedPtr destructor called.
~Resource(): Resource released.
~ControlBlock(): ControlBlock released.
*/

void test_weak_references()
{
	// an empty WeakPtr 
	WeakPtr<Resource> w_p;
	std::cout << "Empty WeakPtr constructed: " << w_p.use_count() << " SharedPtr managing \n";

	// nested block
	{

		// a SharedPtr
		SharedPtr<Resource> p1{ new Resource };
		std::cout << p1.use_count() << " SharedPtr (p1) is managing " << *p1 << "\n";

		// w_p WeakPtr copy-assigned from p1 SharedPtr
		w_p = p1;
		std::cout << w_p.weak_count() << " WeakPtr (w_p copy-assigned from p1) is observing\n";
		
		std::cout << "p1 goes out of scope...\n";

	} // p1 goes out of scope --> Resource released

	std::cout << w_p.use_count() << " SharedPtr are strong-referencing the Resource\n";

	std::cout << "w_p goes out of scope...\n";

} // w_p goes out of scope --> ControlBlock released

/*
Empty WeakPtr constructed: 0 SharedPtr managing
Resource acquired
1 SharedPtr (p1) is managing a Resource(n=1)
WeakPtr assignment operator= (from SharedPtr) called.
1 WeakPtr (w_p copy-assigned from p1) is observing
p1 goes out of scope...
~SharedPtr destructor called.
~Resource(): Resource released.
0 SharedPtr are strong-referencing the Resource
w_p goes out of scope...
~WeakPtr destructor called.
~ControlBlock(): ControlBlock released.
*/

void test_lock()
{
	// a SharedPtr
	SharedPtr<Resource> p1{ new Resource };
	std::cout << p1.use_count() << " SharedPtr (p1) is managing " << *p1 << "\n";

	// a WeakPtr from the SharedPtr
	WeakPtr<Resource> w_p{ p1 };
	std::cout << w_p.weak_count() << " WeakPtr (w_p copy-constructed from p1) is observing\n";

	// a SharedPtr from the locked WeakPtr
	auto s_w_p = w_p.lock();
	std::cout << s_w_p.use_count() << " SharedPtr (p1, s_w_p from w_p.lock()) are managing " << *s_w_p << "\n";

}

/*
Resource acquired
1 SharedPtr (p1) is managing a Resource(n=1)
WeakPtr copy-ctor (from SharedPtr) called.
1 WeakPtr (w_p copy-constructed from p1) is observing
SharedPtr ctor from WeakPtr called.
2 SharedPtr (p1, s_w_p from w_p.lock()) are managing a Resource(n=1)
~SharedPtr destructor called.
~WeakPtr destructor called.
~SharedPtr destructor called.
~Resource(): Resource released.
*/