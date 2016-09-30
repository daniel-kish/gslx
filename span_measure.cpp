#include <iostream>
#include "gsl/gsl"
#include <chrono>
#include <vector>

int main(int argc, char* argv[])
{
	using namespace std;
	using namespace chrono;
	using namespace gsl;
	int sz = (argc > 1)? stoi(argv[1]) : 100'000'000;
	vector<int> v(sz);
	span<int> sp(v);

	int times{50};

	duration<double,milli> d;
	for (int i=0; i < times; ++i)
	{
		auto s = high_resolution_clock::now();
		for (auto& e : sp)
			e++;
		auto f = high_resolution_clock::now();
		d += (f-s);
	}
	cout << d.count() / double(times) << '\n';
}
