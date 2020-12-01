#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#include <iostream>
#include "SharedPtr.h"

template <class T>
class WeakPtr {

	// SharedPtr<T> is friend of WeakPtr<T> (only with same T)
	// needed to access private members of WeakPtr<T> from SharedPtr<T>
	friend class SharedPtr<T>;

	T* m_ptr;
	ControlBlock<T>* m_cb;

	// weak-reference increment method
	void inc_weak()
	{
		// True if there is an allocated ControlBlock
		if (m_cb)
		{
			++(m_cb->count_weak);
		}
	}

	// weak-reference decrement method
	void dec_weak()
	{
		// True if:
		// - there is an allocated ControlBlock
		// - the strong-reference counter reaches zero
		// - the decremented weak-reference counter reaches zero
		if (m_cb && !(m_cb->count_strong) && !(--(m_cb->count_weak)))
		{
			// release ControlBlock
			delete m_cb;
		}
	}
public:

	// default ctor
	WeakPtr() : m_ptr{ nullptr }, m_cb{ nullptr }
	{
	}

	// ctor from SharedPtr
	WeakPtr(const SharedPtr<T>& shared_ptr) : m_ptr{ shared_ptr.m_ptr }, m_cb{ shared_ptr.m_cb }
	{
		std::cout << "WeakPtr copy-ctor (from SharedPtr) called.\n";
		inc_weak();
	}

	// destructor
	~WeakPtr()
	{
		std::cout << "~WeakPtr destructor called.\n";
		dec_weak();
	}

	// overloaded assignment operator= from SharedPtr
	WeakPtr& operator=(const SharedPtr<T>& shared_ptr)
	{
		std::cout << "WeakPtr assignment operator= (from SharedPtr) called.\n";

		// assign pointers to original's resource
		m_ptr = shared_ptr.m_ptr;
		m_cb = shared_ptr.m_cb;

		// increment (this->m_cb)->count_weak counter
		inc_weak();

		return *this;
	}

	// deleted overloaded operator->
	T& operator*() const = delete;

	// deleted overloaded operator*
	T* operator->() const = delete;

	// strong-reference count
	int use_count() const
	{
		// returns True if there is an allocated ControlBlock
		//return (m_cb ? m_cb->count_strong : 0);
		if (m_cb)
		{
			return  m_cb->count_strong;
		}
		else
		{
			return 0;
		}
	}

	// weak-reference count (just for clarity)
	int weak_count() const
	{
		// returns True if there is an allocated ControlBlock
		return (m_cb ? m_cb->count_weak : 0);
	}

	// weak- to shared- pointer converted
	SharedPtr<T> lock() const
	{
		// returns a SharedPtr managing the resource observed by *this,
		// or an empty Shared
		// return ((use_count() == 0)? SharedPtr<T>() : SharedPtr<T>(*this));
		if (use_count() == 0)
		{
			return SharedPtr<T>();
		}
		else
		{
			return SharedPtr<T>(*this);
		}
	}
};

#endif