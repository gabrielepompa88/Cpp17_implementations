#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>

// to make templated class SharedPtr visible inside ControlBlock templated class
template <class T>
class SharedPtr;

template <class T>
class ControlBlock {

	T* m_ptr;
	int count;

	// destroy() method to release Resource
	void destroy()
	{
		delete m_ptr;
	}

public:

	// ctor
	ControlBlock(T* ptr) : m_ptr{ ptr }, count{ 1 }
	{
	}

	// SharedPtr<T> is friend of ControlBlock<T> (only with same T)
	friend class SharedPtr<T>;

};

template <class T>
class SharedPtr {

	T* m_ptr;
	ControlBlock<T>* m_cb;

	// increment method
	void inc()
	{
		// True if there is an allocated ControlBlock
		if (m_cb)
		{
			++(m_cb->count);
		}
	}

	// decrement method
	void dec()
	{
		// True if:
		// - there is an allocated ControlBlock
		// - the decremented reference counter reaches zero
		if (m_cb && !(--(m_cb->count)))
		{
			// release Resource
			m_cb->destroy();

			// release ControlBlock
			delete m_cb;
		}
	}
public:

	// default ctor
	SharedPtr() : m_ptr{ nullptr }, m_cb{ nullptr }
	{
	}

	// ctor
	SharedPtr(T* ptr) : m_ptr{ ptr }, m_cb{new ControlBlock<T>(ptr)}
	{
	}

	// copy ctor
	SharedPtr(const SharedPtr& original) 
		: m_ptr{ original.m_ptr }, m_cb{original.m_cb}
	{
		std::cout << "SharedPtr copy-ctor called.\n";
		inc();
	}

	// overloaded assignment operator=
	SharedPtr& operator=(const SharedPtr& original)
	{
		std::cout << "SharedPtr assignment operator= called.\n";

		// self-assignment check
		if (this != &original)
		{
			// decrement current counter
			dec();

			// assign pointers to original's resource
			m_ptr = original.m_ptr;
			m_cb = original.m_cb;

			// increment newly assigned counter
			inc();
		}

		return *this;
	
	}

	// destructor
	~SharedPtr()
	{
		std::cout << "~SharedPtr destructor called.\n";
		dec();
	}

	// overloaded operator->
	T& operator*() const { return *m_ptr; }
	
	// overloaded operator*
	T* operator->() const { return m_ptr; }

	// reference count
	int use_count()
	{
		// True if there is an allocated ControlBlock
		if (m_cb)
		{
			return m_cb->count;
		}
		else
		{
			return 0;
		}
	}

};

#endif
