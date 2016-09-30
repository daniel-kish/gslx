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

	const int n = SIZE;
	const int m = n;
	vector<int> v(n*m,1);

	// use span fixed size
	{
		cout << setw(wid)  << "span fixed size: ";
		span<int, SIZE * SIZE> fixed_sp(v.data(),v.size());
		auto s = high_resolution_clock::now();
		for (int& e : fixed_sp)
			e++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
	// use dynamic size span
	{
		cout << setw(wid)  << "span dynamic size: ";
		span<int> sp(v);
		auto s = high_resolution_clock::now();
		for (int& e : sp)
			e++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
	// use range-based for loop
	{
		cout << setw(wid)  << "range-based for loop: ";
		auto s = high_resolution_clock::now();
		for (int& e : v) e++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
	// use std::for_each
	{
		cout << setw(wid)  << "std::for_each: ";
		auto s = high_resolution_clock::now();
		std::for_each(begin(v), end(v), [](int& e) { e++; });
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
	// use C-style for loop on pointers
	{
		cout << setw(wid)  << "C-style ptr for loop: ";
		auto s = high_resolution_clock::now();
		const int * end = v.data() + v.size();
		for (int* p = v.data(); p != end; ++p)
			(*p)++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
	// use C-style for loop on indices
	{
		cout << setw(wid)  << "C-style indices for loop: ";
		auto s = high_resolution_clock::now();
		const int sz = v.size();
		for (int i = 0; i < sz; ++i)
			v[i]++;
		auto f = high_resolution_clock::now();
		cout << v[n / 2] << ' ';
		cout << duration_cast<milliseconds>(f - s).count() << '\n';
	}
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
}
