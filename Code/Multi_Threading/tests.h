#ifndef TESTS_H
#define TESTS_H

#include <thread> // for std::thread
#include <iostream>
#include <vector>
#include <algorithm>


// test_counter() using static-polymorphism: all <T> must implement .reset(), .inc(), .dec() and .get() 
// interface methods
template <class T>
void test_counter(T& counter, int iter_max = 10000, int thread_num = 50, int loops_per_thread = 100)
{
	// test is repeated iter_max times and results are stored in a vector
	std::vector<int> results;

	for (int iter = 1; iter <= iter_max; ++iter)
	{
		//std::cout << "Iteration #" << iter << "\n";

		// counter instance reset (to zero)
		counter.reset();

		//std::cout << "START: n=" << counter.get() << "\n";

		// define a vector of std::thread
		std::vector<std::thread> multi_threads;

		// thread_num threads, each one should leave the counter in its current state (to zero)
		for (int i = 0; i < thread_num; ++i) {

			// lambda representing the code that should leave the counter unchanged
			auto leave_counter_unchanged{ [&counter, loops_per_thread]() {
				// for loops_per_thread times a counter increment is repeated, followed by a decrement
				for (int i = 0; i < loops_per_thread; ++i) {
					counter.inc();
					counter.dec(); // this operation should offset the former one
					}
				}
			};

			// thread instantiated (that is, started)
			multi_threads.push_back(std::thread(leave_counter_unchanged));
		}

		for (auto& t : multi_threads)
		{
			t.join(); // makes test_counter() thread to wait for the other threads to terminate
		}

		//std::cout << "END: n=" << counter.get() << " (expecting: n=0)\n\n";

		// store current value of n in results vector
		results.push_back(counter.get());

	}

	// compute the minimum and maximum value of n found
	const auto [min_n, max_n] = std::minmax_element(results.begin(), results.end());

	// print 
	std::cout << "Results [test repeated = " << iter_max <<" times; #threads = "<< thread_num << "; #loops per thread = "<< loops_per_thread << " ): min(n)=" << *min_n << " - " << "max(n)=" << *max_n << "\n";
}

#endif
