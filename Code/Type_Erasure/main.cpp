#include <iostream>
#include <vector>

#include "tests.h"

int main() {

	// test Type Erasure using Object/Concept/Model inheritance pattern
	std::cout << "test_type_erasure_inheritance():\n";
	test_type_erasure_inheritance();

	// test Type Erasure using std::function
	std::cout << "\n\ntest_type_erasure_std_function():\n";
	test_type_erasure_std_function();

	return 0;

}