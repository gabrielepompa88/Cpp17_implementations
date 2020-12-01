#ifndef CIRCULAR_DEPENDENCIES_H
#define CIRCULAR_DEPENDENCIES_H

#include <iostream>
//#include "SharedPtr.h"
#include "WeakPtr.h"

class SelfReferencingResource
{
public:
	// SharedPtr<SelfReferencingResource> m_ptr; // SharedPtr initially empty
	WeakPtr<SelfReferencingResource> m_ptr; // WeakPtr initially empty - to solve circular dependency

	SelfReferencingResource(){std::cout << "SelfReferencingResource acquired\n";}
	~SelfReferencingResource(){std::cout << "~SelfReferencingResource(): SelfReferencingResource released.\n";}

	friend std::ostream& operator<<(std::ostream& out, const SelfReferencingResource& res)
	{
		return std::cout << "a SelfReferencingResource";
	}
};

#endif