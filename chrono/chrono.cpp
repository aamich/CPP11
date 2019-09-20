#include <iostream>
#include <chrono>

using namespace std;

template <typename T1, typename T2>
auto sum(const T1& t1, const T2& t2)->decltype(t1+t2)  {
	return t1+t2;
}

int main() {
	//chrono::time_point<std::chrono::steady_clock> start, end;
	auto start=std::chrono::steady_clock::now();
	auto list={1.f,2.f,3.f,4.f,5.1f};
	cout << "initializer_list:" << endl;
	for(auto i : list)
		cout << i << " ";
	cout << endl;
	float s=0;
	int cnt = 100000000;					// repeating to test timer
	for(int c=0; c < cnt; ++c)
	for(auto i : list) {
		s = sum(s, i);
	}
	cout << "s=" << s << endl;
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	cout << "elapsed time: " << elapsed_seconds.count() << " s" << endl;	// seconds
	cout << "= " << (end-start).count() << " ns" << endl;					// nanoseconds
}
