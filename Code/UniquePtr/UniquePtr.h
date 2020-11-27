#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <class T>
class UniquePtr {

	T* m_ptr;

public:

	// default ctor
	UniquePtr(T* ptr = nullptr) : m_ptr{ptr}
	{
	}

	// destructor
	~UniquePtr()
	{
		delete m_ptr;
	}

	// copy ctor deleted
	UniquePtr(const UniquePtr& original) = delete;

	// move ctor
	UniquePtr(UniquePtr&& original)
	{
		std::cout << "move operator= called\n";

		m_ptr = original.m_ptr;   // shallow copy of T-ptrs  
		original.m_ptr = nullptr; // moved ptr left to default state
	}

	// overloaded copy-assignment operator= deleted
	UniquePtr& operator=(const UniquePtr& original) = delete;

	// overloaded move-assignment operator=
	UniquePtr& operator=(UniquePtr&& original) noexcept
	{
		std::cout << "move operator= called\n";

		if (!(this == &original))
		{
			delete m_ptr;             // release any resource possibly handled already

			m_ptr = original.m_ptr;   // shallow copy of T-ptrs  
			original.m_ptr = nullptr; // moved ptr left to default state
		}

		return *this;
	}

	// overloaded operator->
	T& operator*() const { return *m_ptr; }
	
	// overloaded operator*
	T* operator->() const { return m_ptr; }

	// check whether UniquePtr is empty
	bool isNull() const { return m_ptr == nullptr; }

};

#endif
