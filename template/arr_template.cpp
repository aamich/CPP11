#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <cassert>

using namespace std;

template <typename T1, typename T2>
auto sum(const T1& t1, const T2& t2)->decltype(t1+t2)  {
	return t1+t2;
}

class Base {
public:
	Base() {
		cout << "Base" << endl;
	}
};

class Derived: public Base {
	Derived(): Base() {
		cout << "Derived" << endl;
	}
};

int& func_static_int() {
	static int i=10;
	return i;
}

struct Throw {
	Throw(){
		throw 'c';
	}
};

template <typename T>
class Array {
public:
	Array(){}
	Array(int len): _len(len) { _data = new T[_len]; }
	Array(const initializer_list<T>& list): Array(list.size()) {
		int cnt = 0;
		for(auto& it: list) {
			_data[cnt++] = it;
		}
	}
	~Array(){}
	int size() const { return _len; }
	T& operator[](int i) {
		assert(0 <= i && i < _len);
		return _data[i];
	}
	void printall() const { 
		for(int i=0; i < _len; ++i)
			cout << _data[i] << " ";
	}
private:
	T* _data{nullptr};
	int _len{0};
};

int main() {
	//chrono::time_point<std::chrono::steady_clock> start, end;
	auto start=std::chrono::steady_clock::now();
	auto list={1.f,2.f,3.f,4.f,5.1f};
	cout << "initializer_list: list = ";
	for(auto i : list)
		cout << i << " ";
	cout << endl;
	float s=0;
	int cnt = 1000000;					// repeating to test timer
	for(int c=0; c < cnt; ++c)
	for(auto i : list) {
		s = sum(s, i);
	}
	cout << "sum(list)*1000000=" << s << endl;
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	cout << "elapsed time: " << elapsed_seconds.count() << " s";		// seconds
	cout << "= " << (end-start).count() << " ns" << endl;				// nanoseconds

	// rvalue
	int x=0;
	int& x1 = x;
	int&& xr = 0;
	typedef std::vector<int> IntVec;
	IntVec iv;
	iv.push_back(xr);
	iv.push_back(std::move(x));
	cout << "after move(x), x=" << x << endl;
	cout << "iv.size()=" << iv.size() << endl;

	// array
	array<int, 5> arr{1,3,2,4,5};
	cout << "array of 5 ints, arr.size()=" << arr.size() << endl;
	cout << "sizeof(arr)=" << sizeof(arr) << endl;

	array<char, 1> ca{'a'};
	cout <<  "sizeof(ca), one char, = " << sizeof(ca) << endl;

	// empy class Base, sizeof(Base)==1
	Base b;
	cout << sizeof(b) << endl;

	// static variable inside a function
	cout << func_static_int();
	cout << endl;
	func_static_int() = 20;
	cout << func_static_int();
	cout << endl;

	cout << "25u-50="<< 25u-50 << endl;		// garbage result
	cout << "25u-50u="<< 25u-50u << endl;	// garbage result
	cout << "25u+50="<<25u + 50 << endl;	// good result
	cout << "25u+50u="<<25u + 50u << endl;	// good result

	// test try...catch...
	try {
		throw 30;
	}
	catch (int e) {
		cout << e << endl;
	}
	try {
		Throw th; // throw char 'c'
		throw 200;	// throw int 200
	}
	catch (int e) {
		cout << e << endl;	// won't catch int 200
	}
	catch (char c) {
		cout << c << endl;	// it catches char 'c'
	}

	// default initialization
	struct A {
		//string a{"test"};
		float b{3.14f};
		char c{'c'};
	} a;

	// test sizeof
	auto t=std::make_tuple(3.14f,'c', 100);
	float f; char c; int i;
	std::tie (f, c, i) = t;
	cout << f << " " << c << " " << i << endl;
	string str="test";
	cout << str.size() << " " << str.capacity() << endl;
	cout << sizeof(str) << " " << sizeof(3.14f) << " " << sizeof(a) << " " << sizeof(t) << endl;
	cout << "ceiling of 3.14=" << ceil(3.14) << endl;
	cout << "floor of 3.14=" << floor(3.14) << endl;
	cout << "ceiling of 3=" << ceil(3.0) << endl;
	cout << "floor of 3=" << floor(3.0) << endl;

	// test self defined array of any type
	auto Arr = Array<int>{1,3,5,9,7,13};
	cout << Arr.size() << endl;
	cout << "Arr[0]=" << Arr[0] << endl;
	Arr.printall();
	cout << endl;
}
