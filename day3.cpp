#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
std::vector<std::vector<bool>> get_data_day3(char* filename) {
    std::ifstream file(filename);
    std::vector<std::vector<bool>> d;
    std::string buffer;
    while (std::getline(file, buffer)) {
        std::vector<bool> line;
        for (auto c : buffer) {
            line.push_back(c != '.');
        }
        d.push_back(line);
    }
    return d;
}

auto main(int argc, char* argv[]) -> int {
    auto d = get_data_day3(argv[1]);
    std::vector<int> ctrs;
    std::vector<std::vector<int>> slopes{
        {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

    for (auto v : slopes) {
        int ctr = 0;
        for (int i = 0; i * v[1] < d.size(); i++) {
            if (d[v[1] * i][(v[0] * i) % d[0].size()])
                ctr++;
        }
        ctrs.push_back(ctr);
    }
    for (auto ctr : ctrs)
        std::cout << "ctr: " << ctr << std::endl;
    std::cout << "product: "
              << std::accumulate(ctrs.begin(), ctrs.end(), 1,
                                 std::multiplies<int>())
              << std::endl;

    return 0;
}
