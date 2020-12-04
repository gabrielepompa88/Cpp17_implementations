#ifndef SHARED_PTR_H
#define SHARED_PTR_H

// This version of SharedPtr class, includes a counter for weak-references

#include <iostream>

// to make templated class SharedPtr visible inside ControlBlock templated class
template <class T>
class SharedPtr;

// to make templated class WeakPtr visible inside ControlBlock templated class
template<class T>
class WeakPtr;

template <class T>
class ControlBlock {

	T* m_ptr;
	int count_strong; // "strong-reference" counter (# of SharedPtr managing the resource)
	int count_weak;  // "weak-reference" counter (# of WeakPtr observing the resource)

	// destroy() method to release Resource
	void destroy()
	{
		delete m_ptr;
	}

public:

	// ctor
	ControlBlock(T* ptr) : m_ptr{ ptr }, count_strong{ 1 }, count_weak{ 0 }
	{
	}

	// destructor (just for printing)
	~ControlBlock()
	{
		std::cout << "~ControlBlock(): ControlBlock released.\n";
	}

	// SharedPtr<T> is friend of ControlBlock<T> (only with same T)
	// needed to access m_cb->count_strong from SharedPtr<T>
	friend class SharedPtr<T>;

	// WeakPtr<T> is friend of ControlBlock<T> (only with same T)
	// needed to access m_cb->count_strong from WeakPtr<T>
	friend class WeakPtr<T>;

};

template <class T>
class SharedPtr {


	// WeakPtr<T> is friend of SharedPtr<T> (only with same T)
	// needed to access private members of SharedPtr<T> from WeakPtr<T>
	friend class WeakPtr<T>;

	T* m_ptr;
	ControlBlock<T>* m_cb;

	// strong-reference increment method
	void inc()
	{
		// True if there is an allocated ControlBlock
		if (m_cb)
		{
			++(m_cb->count_strong);
		}
	}

	// strong-reference decrement method
	void dec()
	{
		// True if:
		// - there is an allocated ControlBlock
		// - the decremented strong-reference counter reaches zero
		if (m_cb && !(--(m_cb->count_strong)))
		{
			// release Resource
			m_cb->destroy();

			// ControlBlock released only if there are no WeakPtr observing the resource
			if (!(m_cb->count_weak)) {
				// release ControlBlock
				delete m_cb;
			}
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
		: m_ptr{ original.m_ptr }, m_cb{ original.m_cb }
	{
		std::cout << "SharedPtr copy-ctor called.\n";
		inc();
	}

	// ctor from WeakPtr<T> (called from WeakPtr<T>::lock())
	SharedPtr(const WeakPtr<T>& weak_ptr)
		: m_ptr{ weak_ptr.m_ptr }, m_cb{ weak_ptr.m_cb }
	{
		std::cout << "SharedPtr ctor from WeakPtr called.\n";
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

	// strong-reference count
	int use_count() const
	{
		// returns True if there is an allocated ControlBlock
		return (m_cb ? m_cb->count_strong : 0);
	}
};

#endif