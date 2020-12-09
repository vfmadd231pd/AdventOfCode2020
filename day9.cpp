#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
int64_t part1(const std::vector<int64_t>& d, const int64_t p) {
    for (int i = p; i < d.size(); i++) {
        bool found = false; // Found the sum in the preamble..
        for (int j = i - p; j < i; j++) {
            if (std::find(d.begin() + i - p, d.begin() + i, d[i] - d[j]) !=
                d.begin() + i) {
                found = true; // Found it
            }
        }
        if (!found) {
            return d[i];
        }
    }
    return 0;
}
auto main(int argc, char* argv[]) -> int {
    std::cout << "*** DAY 9 ***" << std::endl;
    constexpr const int64_t preamble_length = 5;
    std::ifstream file(argv[1]);
    std::string buffer;
    std::vector<int64_t> data;
    while (std::getline(file, buffer)) {
        data.push_back(std::stoll(buffer));
    }
    int64_t res1 = part1(data, preamble_length);
    std::cout << "Part 1: " << res1 << std::endl;
    for (int i = 0; i < data.size(); i++) {
        int64_t sum = 0;
        for (int j = i; j < data.size(); j++) {
            sum += data[j];
            if (sum == res1) {
                std::cout << "Part 2: "
                          << *std::min_element(data.begin() + i,
                                               data.begin() + j) +
                                 *std::max_element(data.begin() + i,
                                                   data.begin() + j)
                          << std::endl;
                return 0;
            }
        }
    }
    return 0;
}
