#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <fmt/core.h>
#include <fmt/format.h>

int main() {
    size_t num_sets, set_length;
    fmt::print("Input number of sets and length of each set\n");
    std::cin >> num_sets >> set_length;
    constexpr size_t buffer_size = 1024 * 1024;
    const std::string filename = "test_data";

    std::string buffer; buffer.reserve(buffer_size + 100);
    buffer += std::to_string(num_sets); buffer += ' ';
    buffer += std::to_string(set_length); buffer += '\n';

    size_t n = num_sets * set_length;

    std::mt19937_64 rng{std::random_device()()};
    std::uniform_int_distribution<uint32_t> dis(1, n);
    std::ofstream out; out.open(filename);
    fmt::print("Generating and writing {} random numbers between {} and {} to {}\n", n, 1, n, filename);

    while(n--) {
        buffer += fmt::format_int(dis(rng)).str(); buffer += '\n';
        if(buffer.length() >= buffer_size) {
            out.write(buffer.data(), buffer.length());
            buffer.clear();
        }
    }

    if(buffer.length() > 0) {
        out.write(buffer.data(), buffer.length());
    }

    out.close();
    fmt::print("Test data generated and written to {}\n", filename);
}
