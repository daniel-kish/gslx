#include <iostream>
#include "gsl/gsl"
#include <vector>
#include <chrono>
#include <iomanip>

int wid=30;

int main(int argc, char* argv[])
try{	
	using namespace std; using namespace gsl;
	using namespace chrono;

	int n = 10'000;
	int m = n;
	vector<int> v(n*m,1);

	// use dynamic size multi_span
	{
		cout << setw(wid)  << "span dynamic size: ";
		static_bounds<dynamic_range,dynamic_range> bnd{n,m};
		multi_span<int,dynamic_range,dynamic_range> sp(v.data(), bnd);
		auto s = high_resolution_clock::now();
		for (int& e : sp)
			e++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
	// use dynamic size multi_span indexed
	{
		cout << setw(wid)  << "indexed: ";
		static_bounds<dynamic_range,dynamic_range> bnd{n,m};
		multi_span<int,dynamic_range,dynamic_range> sp(v.data(), bnd);
		auto s = high_resolution_clock::now();
		for (index<2> idx : sp.bounds())
			sp[idx]++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
	// use C-style for loop on indices
	{
		cout << setw(wid)  << "C-style indices for loop: ";
		auto s = high_resolution_clock::now();
		int* p = v.data();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				p[i*m + j]++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
}
