#include "fourier.h"

#include <algorithm>
#include <cmath>

using namespace std;


typedef vector<complex<double>> fft_res;

static complex<double> * dft_simple_helper(complex<double> *x, size_t N) {
	complex<double> *X = static_cast<complex<double> *>(calloc(N, sizeof(complex<double>)));
	if (N == 1) {
		X[0] = x[0];
		return X;
	}

	complex<double> *d = static_cast<complex<double> *>(calloc(N / 2, sizeof(complex<double>)));
	complex<double> *e = static_cast<complex<double> *>(calloc(N / 2, sizeof(complex<double>)));
	for (size_t k = 0; k < N/2; ++k) {
		e[k] = x[2*k];
		d[k] = x[2*k + 1];
	}

	complex<double> *D = dft_simple_helper(d, N/2);
	complex<double> *E = dft_simple_helper(e, N/2);
	free(d);
	free(e);
	for (size_t k = 0; k < N/2; ++k) {
		double rotation = -2.0 * M_PI * k / static_cast<double>(N);
		D[k] *= polar(1.0, rotation);
	}

	for (size_t k = 0; k < N/2; ++k) {
		X[k] = E[k] + D[k];
		X[k + N/2] = E[k] - D[k];
	}

	free(D);
	free(E);
	return X;
}

std::vector<complex<double>> naive_dft(const std::vector<uint8_t> &x) {
	fft_res res;
	res.resize(x.size());
	
	for (size_t k = 0; k < x.size(); ++k) {
		complex<double> zero(0.0, 0.0);
		res[k] = zero;
		for (size_t n = 0; n < x.size(); ++n) {
			complex<double> x_n(static_cast<double>(x[n]), 0.0);
			double rotation = (-2.0*M_PI*n*k) / static_cast<double>(x.size());
			res[k] += x_n * polar(1.0, rotation);
		}
	}

	return res;
}

std::vector<std::complex<double>> naive_dft_better(const std::vector<uint8_t> &x) {
	fft_res res;
	res.resize(x.size());

	fft_res roots;
	roots.resize(x.size());
	for (size_t k = 0; k < x.size(); ++k) {
		double rotation = -2.0*M_PI*k / static_cast<double>(x.size());
		roots[k] = polar(1.0, rotation);
	}
	for (size_t k = 0; k < x.size(); ++k) {
		res[k] = complex<double>(0.0, 0.0);
		for (size_t n = 0; n < x.size(); ++n) {
			complex<double> x_n(static_cast<double>(x[n]), 0.0);
			res[k] += x_n * roots[n*k % x.size()];
		}
	}
	return res;
}

std::vector<std::complex<double>> dft_simple(const std::vector<uint8_t> &x) {
	complex<double> *converted = static_cast<complex<double> *>(calloc(x.size(), sizeof(complex<double>)));
	complex<double> *it = converted;
	for (size_t i = 0; i < x.size(); ++i) {
		new (it) complex<double>(static_cast<double>(x[i]), 0.0);
		it += 1;
	}
	complex<double> *X = dft_simple_helper(converted, x.size());
	free(converted);
	fft_res res;
	res.resize(x.size());
	copy(X, X + x.size(), res.begin());
	return res;
}