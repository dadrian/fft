#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "fourier.h"

using namespace std;

template<typename T>
void print_vec(const vector<T> &v) {
	for_each(v.begin(), v.end(), [](const T& elt) {
		cout << elt << ", ";
	});
	cout << endl;
}

int main(int argc, char *argv[]) {
	std::vector<uint8_t> x;
	x.resize(4);
	x[0] = 4;
	x[1] = x[2] = x[3] = 0;
	cout << "Naive FFT [4, 0, 0, 0]: ";
	auto naive_res = naive_dft(x);
	print_vec(naive_res);
	cout << "Less Naive FFT [4, 0, 0, 0]: ";
	auto less_naive_res = naive_dft_better(x);
	print_vec(less_naive_res);
	cout << "FFT [4, 0, 0, 0]: ";
	auto fft_res = dft_simple(x);
	print_vec(fft_res);
	vector<uint8_t> in(1024);
	transform(in.begin(), in.end(), in.begin(), [](const uint8_t& elt) {
		static uint8_t i = 0;
		return i++;
	});
	cout << "FFT [0:255, 0:255, 0:255, 0:255]: " << endl;
	auto in_res = dft_simple(in);
	print_vec(in_res);
	/*
	cout << "Making big vec..." << endl;
	srand(time(0));
	vector<uint8_t> big;
	big.resize(10584000);
	transform(big.begin(), big.end(), big.begin(), [](const uint8_t& elt) {
		return static_cast<uint8_t>(rand() % 256);
	});

	cout << "FFTing..." << endl;
	auto long_res = naive_dft_better(big);
	cout << "Done" << endl;
	*/
	return 0;
}