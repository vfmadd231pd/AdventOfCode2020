#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

auto main(int argc, char* argv[]) -> int {
    std::ifstream file(argv[1]);
    std::string buffer;
    std::vector<int> data;
    while (std::getline(file, buffer)) {
        data.push_back(std::stoi(buffer));
    }

    std::unordered_map<int, int> data_map;
    data_map.reserve(data.size());
    constexpr int magic_number = 2020;
    for (auto v : data)
        data_map[magic_number - v] = v;

    for (const auto& [k, v] : data_map) {
        if (data_map.find(v) != data_map.end()) {
            std::cout << "Part 1: " << v << " * " << k << " = " << k * v
                      << std::endl;
            break;
        }
    }
    for (const auto& [k1, v1] : data_map) {
        for (const auto& [k2, v2] : data_map) {
            if (data_map.find(v1 + v2) != data_map.end()) {
                std::cout << "Part 2: " << v1 << " * " << v2 << " * "
                          << (k1 - v2) << " = " << v1 * v2 * (k1 - v2)
                          << std::endl;
                return 0;
            }
        }
    }
    return 0;
}
