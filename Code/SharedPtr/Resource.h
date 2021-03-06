#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

class Resource {

	int m_n;

public:

	Resource(int n = 1) : m_n{n}
	{
		std::cout << "Resource (n=" << m_n<< ") acquired\n";
	}

	~Resource()
	{
		std::cout << "Resource (n=" << m_n << ") destroyed.\n";
	}

	friend std::ostream& operator<<(std::ostream& out, const Resource& res)
	{
		return std::cout << "a Resource(n=" << res.m_n << ")";
	}
};
#endif
