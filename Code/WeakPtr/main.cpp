#include <iostream>
#include "tests.h"

int main() {

	// test SharedPtr behaves as expected when nested blocks make
	// other SharedPtr (referencing the same Resource) going out of scope
	std::cout << "\n\ntest_nested_blocks()\n";
	test_nested_blocks();

	// test that two SharedPtr independently referencing the (same) Resource,
	// can be assigned to be coherent references
	std::cout << "\n\ntest_resource_reassignment()\n";
	test_resource_reassignment();

	// test that WeakPtr can be copy constructed from SharedPtr and that 
	// the ControlBlock is released only when count_weak is zero
	// (even if the count_strong is already zero)
	std::cout << "\n\ntest_weak_references()\n";
	test_weak_references();

	// test that WeakPtr can be locked into a SharedPtr
	std::cout << "\n\ntest_weak_pointers()\n";
	test_lock();

	// test that WeakPtr solves a circular dependency
	std::cout << "\n\ntest_weak_pointers()\n";
	test_circular_dependencies();

	return 0;
}

/*

if SelfReferencingResource::m_ptr is SharedPtr:

SelfReferencingResource acquired
1 SharedPtr(s_p) is managing a SelfReferencingResource
SharedPtr assignment operator= called.
2 SharedPtr(s_p and s_p->m_ptr) are managing a SelfReferencingResource
~SharedPtr destructor called.

if SelfReferencingResource::m_ptr is WeakPtr:

SelfReferencingResource acquired
1 SharedPtr (s_p) is managing a SelfReferencingResource
WeakPtr assignment operator= (from SharedPtr) called.
1 SharedPtr (s_p) is managing a SelfReferencingResource
1 WeakPtr (s_p->m_ptr copy-assigned from p1) is observing
~SharedPtr destructor called.
~SelfReferencingResource(): SelfReferencingResource released.
~WeakPtr destructor called.
~ControlBlock(): ControlBlock released.

*/