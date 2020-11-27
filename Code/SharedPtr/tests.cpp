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

void test_resource_reassignment()
{
	// Resource referenced by p_res
	SharedPtr<Resource> p_res{ new Resource };
	std::cout << "p_res says: " << p_res.use_count() << " SharedPtr are referencing " << *p_res << "\n";

	// Resource referenced by p_other_res independently
	SharedPtr<Resource> p_other_res{ new Resource };
	std::cout << "p_other_res says: " << p_other_res.use_count() << " SharedPtr are referencing " << *p_other_res << "\n";

	// make p_other_res another reference of Resource, in addition to p_res
	p_other_res = p_res;

	std::cout << "p_res (p_other_res) says: " << p_res.use_count() << "(" << p_other_res.use_count() << ") SharedPtr are referencing " << *p_res << "(" << *p_other_res << ")\n";
}
