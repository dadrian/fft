#include <complex>
#include <vector>
#include <cstdint>

std::vector<std::complex<double>> naive_dft(const std::vector<uint8_t> &x);
std::vector<std::complex<double>> naive_dft_better(const std::vector<uint8_t> &x);
std::vector<std::complex<double>> dft_simple(const std::vector<uint8_t> &x);
