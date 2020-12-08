#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

auto main(int argc, char* argv[]) -> int {
    std::cout << "**** DAY 5 ****\n";
    std::ifstream file(argv[1]);
    constexpr const int rows = 7;
    constexpr const int cols = 2;
    std::string s;
    int max_seatID = 0;
    int min_seatID = 100000000;
    long sum_of_ids = 0;
    while (std::getline(file, s)) {
        std::for_each(s.begin(), s.end(), [](char& c) {
            if (c == 'B' || c == 'R')
                c = '1';
            else
                c = '0';
        });
        int candidate_seatID = std::stoi(s.c_str(), nullptr, 2);
        sum_of_ids += candidate_seatID;
        if (candidate_seatID > max_seatID) {
            max_seatID = std::stoi(s, nullptr, 2);
        }
        if (candidate_seatID < min_seatID) {
            min_seatID = std::stoi(s, nullptr, 2);
        }
    }
    std::cout << "Part 1: " << max_seatID << std::endl;
    int your_seatID = max_seatID * (max_seatID + 1) / 2 -
                      min_seatID * (min_seatID - 1) / 2. - sum_of_ids;
    std::cout << "Part 2: " << your_seatID << std::endl;
    return 0;
}
