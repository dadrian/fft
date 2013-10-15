#ifndef FOURIER_H
#define FOURIER_H

#include <complex>
#include <vector>
#include <cstdint>

const size_t k_fourier_frame_size = 1024;

std::vector<std::complex<double>> naive_dft(const std::vector<int16_t> &x);
std::vector<std::complex<double>> naive_dft_better(const std::vector<int16_t> &x);
std::vector<std::complex<double>> dft_simple(const std::vector<int16_t> &x, const size_t &first);

#endif /* FOURIER_H */