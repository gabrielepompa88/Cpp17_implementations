#include <iostream>
#include <memory> // for std::move
#include "UniquePtr.h"
#include "Resource.h"

int main() {

	UniquePtr<Resource> p1{ new Resource };
	UniquePtr<Resource> p2;

	std::cout << "p1 is managing Resource? " << (p1.isNull() ? "No.": "Yes!") << "\n";
	std::cout << "p2 is managing Resource? " << (p2.isNull() ? "No.": "Yes!") << "\n";

	std::cout << "Resource exchange...\n";
	p2 = std::move(p1);

	std::cout << "p1 is managing Resource? " << (p1.isNull() ? "No." : "Yes!") << "\n";
	std::cout << "p2 is managing Resource? " << (p2.isNull() ? "No." : "Yes!") << "\n";

	return 0;
}
