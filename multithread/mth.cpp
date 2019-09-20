// simple examples to demonstrate multithreading in C++11
// 1. lambda function
// 2. regular functions
// 3. functor
// 4. tasks/future

#include <thread>
#include <vector>
#include <iostream>
#include <future>

using namespace std;

// the following two functions are for method 2
// for threading, function can't have return value, results have to
// be transferred by parameters
void addi(const vector<int>& v, int& a) {
	for(auto i : v)
		a += i;
}

void mult(const vector<int>& v, int& m) {
	for(auto i : v)
		m *= i;
}

// the following class's are for method 3
class AddFunctor {
public:
	void operator() (const vector<int>& v) {
		_add = 0;
		for(auto i : v)
			_add += i;
	}
	unsigned _add;
};

class MulFunctor {
public:
	void operator() (const vector<int>&v) {
		_mul = 1;
		for(auto i : v)
			_mul *= i;
	}
	unsigned _mul;
};

int main() {
	{
	    unsigned int c = std::thread::hardware_concurrency();
	    std::cout << "number of cores: " << c << endl;;
	}

	vector<int> v{1,2,3,4,5,6,7,9,8};
	int add=0, mul=1;

	// 1. C++ lambda function
	{
		thread t1([&add, &v] { for (auto i : v) add += i; return add; });
		thread t2([&mul, &v] { for (auto i : v) mul *= i; return mul; });
		// can do other thing in the main thread here
		t1.join();
		t2.join();
		cout << "Method 1, lambda function multithreading" << endl;
		cout << "addition=" << add << endl;
		cout << "multiplication=" << mul << endl;
	}

	// 2. regular function call
	{
		add=0, mul=1;
		thread t1(addi, std::ref(v), std::ref(add));
		thread t2(mult, std::ref(v), std::ref(mul));
		// can do other thing in the main thread here
		t1.join();
		t2.join();
		cout << "Method 2, regular function multithreading" << endl;
		cout << "addition=" << add << endl;
		cout << "multiplication=" << mul << endl;
	}

	// 3. functor
	{
		AddFunctor addFtor = AddFunctor();
		MulFunctor mulFtor = MulFunctor();
		thread t1(std::ref(addFtor), std::ref(v));
		thread t2(std::ref(mulFtor), std::ref(v));
		// can do other thing in the main thread here
		t1.join();
		t2.join();
		cout << "Method 3, functor multithreading" << endl;
		cout << "addition=" << addFtor._add << endl;
		cout << "multiplication=" << mulFtor._mul << endl;
	}

	// 4. future
	// Tasks are defined and created using std::async, instead of threads that are created using std::thread
	// The returned value from std::async is called a std::future, meaning t1 and t2 will be assigned values in the future. 
	// We get their values by calling t1.get() and t2.get()
	// If the future values are not ready, upon calling get() the main thread blocks until the future value becomes ready 
	// (similar to join() ).
	// Notice that the function that we passed to std::async returns a value. 
	// This value is passed through a type called std::promise. The C++ library does that behind the scenes.
	// Each task by default starts as soon as it is created
	{
		auto addFunc = [](vector<int>& v) {
			unsigned add = 0;
			for(auto i : v)
				add += i;
			return add;
		};
		auto mulFunc = [](vector<int>& v) {
			unsigned mul = 1;
			for(auto i : v)
				mul *= i;
			return mul;
		};
		auto t1 = async(addFunc, std::ref(v));
		auto t2 = async(mulFunc, std::ref(v));
		// can do other thing in the main thread here
		unsigned a = t1.get();
		unsigned m = t2.get();
		cout << "Method 4, tasks multithreading" << endl;
		cout << "addition=" << a << endl;
		cout << "multiplication=" << m << endl;
	}
}
