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

	return 0;
}
