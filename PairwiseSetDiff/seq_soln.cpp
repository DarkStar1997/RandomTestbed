#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <argh.h>
#include <iostream>

std::vector<std::set<uint32_t>> pairWiseSetDiff(const std::vector<std::set<uint32_t>> &mat) {
    std::vector<std::set<uint32_t>> res;
    std::vector<uint32_t> indices(mat.size()); std::iota(indices.begin(), indices.end(), 0);
    std::transform(indices.begin(), indices.end(), std::back_inserter(res), [N = mat.size(), &mat](auto i){
        std::set<uint32_t> cur_set;
        std::set_difference(mat[i].begin(), mat[i].end(), mat[(i + 1) % N].begin(), mat[(i + 1) % N].end(),
            std::inserter(cur_set, cur_set.begin()));
        return cur_set;
    });
    return res;
}

void fastInput(std::vector<std::set<uint32_t>> &mat) {
    size_t num_sets, set_length;
    const size_t buffer_size = 1024 * 1024;
    std::cin >> num_sets >> set_length;
    std::getchar();
    size_t n = num_sets * set_length, count = 0, num = 0;
    std::vector<char> buffer; buffer.reserve(buffer_size + 100);
    mat = std::vector<std::set<uint32_t>>(num_sets);

    while(count < n) {
        std::cin.read(buffer.data(), buffer_size);
        size_t len = std::cin.gcount();
        if(len == 0)
            break;

        for(size_t i = 0; i < len; i++) {
            const auto& ch = buffer[i];
            if(std::isdigit(ch))
                num = num * 10 + ch - '0';
            else {
                mat[count / set_length].insert(num);
                num = 0;
                count++;
            }
        }
    }
}

int main(int, char **argv) {
    argh::parser cmdl(argv);
    std::vector<std::set<uint32_t>> mat;
    fmt::print("Preparing input data\n");
    fastInput(mat);
    fmt::print("Input data prepared\n");
    auto start = std::chrono::steady_clock::now();
    auto ans = pairWiseSetDiff(mat);
    auto end = std::chrono::steady_clock::now();
    if(cmdl[{"-d"}]) {
        fmt::print("Input: {}\n Output: {}\n", mat, ans);
    }
    fmt::print("Time taken: {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}
