#include <iostream>
#include <chrono> // for std::chrono

#include "tests.h"
#include "counters.h"

// Multi-threading experiment using std::mutex and std::atomic on a counter class
// Reference: https://baptiste-wicht.com/categories/c%2B%2B11-concurrency-tutorial.html

using namespace std::chrono;

int main() {

	// Multi-Threading Test 1: using CounterUnsafe

	CounterUnsafe counter_unsafe;

	auto t0 = high_resolution_clock::now(); // t0
	test_counter(counter_unsafe);
	auto t1 = high_resolution_clock::now(); // t1

	auto duration_unsafe_counter = duration_cast<seconds>(t1 - t0);
	std::cout << "test_counter() using CounterUnsafe took "<< duration_unsafe_counter.count() << " seconds.\n\n";
	
	//---------------------------------------------------

	// Multi-Threading Test 2: using CounterSafeMutex

	CounterSafeMutex counter_safe_mutex;

	auto t2 = high_resolution_clock::now(); // t2
	test_counter(counter_safe_mutex);
	auto t3 = high_resolution_clock::now(); // t3

	auto duration_mutex = duration_cast<seconds>(t3 - t2);
	std::cout << "test_counter() using std::mutex took " << duration_mutex.count() << " seconds.\n\n";

	//---------------------------------------------------

	// Multi-Threading Test 3: using CounterSafeAtomic

	CounterSafeAtomic counter_safe_atomic;

	auto t4 = high_resolution_clock::now(); // t4
	test_counter(counter_safe_atomic);
	auto t5 = high_resolution_clock::now(); // t5

	auto duration_atomic = duration_cast<seconds>(t5 - t4);
	std::cout << "test_counter() using std::atomic took " << duration_atomic.count() << " seconds.\n\n";

	return 0;

	/* 
	
	Results from a run. Notice that: 
	- using CounterUnsafe the results are not predictable
	- CounterSafeAtomic is more performant than CounterSafeMutex
	
	Results [test repeated = 10000 times; #threads = 50; #loops per thread = 100 ): min(n)=-12 - max(n)=4
	test_counter() using CounterUnsafe took 38 seconds.

	Results [test repeated = 10000 times; #threads = 50; #loops per thread = 100 ): min(n)=0 - max(n)=0
	test_counter() using std::mutex took 46 seconds.

	Results [test repeated = 10000 times; #threads = 50; #loops per thread = 100 ): min(n)=0 - max(n)=0
	test_counter() using std::atomic took 37 seconds.
	*/

}