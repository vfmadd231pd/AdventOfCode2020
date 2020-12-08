#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <vector>

// Requires an extra newline at end of input file
auto main(int argc, char* argv[]) -> int {
    std::cout << "**** DAY 6 ****\n";
    std::ifstream file(argv[1]);
    std::string group;
    std::vector<std::set<char>> vs, vs2;
    std::string line;
    while (std::getline(file, line)) {
        group += line;
        if (line.empty()) {
            std::set<char> s;
            for (auto c : group)
                s.insert(c);
            vs.push_back(s);
            group = "";
        } else {
        }
    }
    file.clear();
    file.seekg(0);
    while (std::getline(file, line)) {
        std::set<char> s1;
        for (auto c : line) {
            s1.insert(c);
        }
        std::set<char> intersect;
        while (std::getline(file, line)) {
            if (line.empty()) {
                vs2.push_back(s1);
                break;
            }
            std::set<char> s2;
            for (auto c : line) {
                s2.insert(c);
            }
            std::set_intersection(s2.begin(), s2.end(), s1.begin(), s1.end(),
                                  std::inserter(intersect, intersect.begin()));
            s1 = intersect;
            intersect.clear();
        }
    }
    std::cout << "Part 1: "
              << std::accumulate(
                     vs.begin(), vs.end(), 0,
                     [](int x, std::set<char> y) { return x + y.size(); })
              << std::endl;
    std::cout << "Part 2: "
              << std::accumulate(
                     vs2.begin(), vs2.end(), 0,
                     [](int x, std::set<char> y) { return x + y.size(); })
              << std::endl;
    return 0;
}
