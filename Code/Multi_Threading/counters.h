#ifndef COUNTERS_H
#define COUNTERS_H

#include <mutex> // for std::mutex
#include <atomic> // for std::atomic

// a non thread-safe counter class
class CounterUnsafe {

	int n;

public:

	// default ctor: set n to zero
	CounterUnsafe() :n{ 0 } {}

	// increment value of n by 1
	void inc()
	{
		++n;
	}

	// decrement value of n by 1
	void dec()
	{
		--n;
	}

	// get current value of n
	int get() const
	{
		return n;
	}

	// reset the value of n to zero
	void reset()
	{
		n = 0;
	}
};

// a thread-safe counter class using mutexes
class CounterSafeMutex {

	// instance of mutex
	std::mutex mutex;

	int n;

public:

	// default ctor: set n to zero
	CounterSafeMutex() :n{ 0 } {}

	// increment value of n by 1
	void inc()
	{
		mutex.lock(); // locking thread 
		++n;
		mutex.unlock(); // unlocking thread
	}

	// decrement value of n by 1
	void dec()
	{
		mutex.lock(); // locking thread
		--n;
		mutex.unlock(); // unlocking thread
	}

	// get current value of n
	int get() const
	{
		return n;
	}

	// reset the value of n to zero
	void reset()
	{
		n = 0;
	}
};


// a thread-safe counter class using atomic variables
class CounterSafeAtomic {

	std::atomic<int> n;

public:

	// default ctor: set n to zero
	CounterSafeAtomic() :n{ 0 } {}

	// increment value of n by 1
	void inc()
	{
		++n;
	}

	// decrement value of n by 1
	void dec()
	{
		--n;
	}

	// get current value of n
	int get() const
	{
		return n.load(); // atomically obtains the value of n
	}

	// reset the value of n to zero
	void reset()
	{
		n = 0; // uses overloaded operator= on atomic object n
	}
};

#endif