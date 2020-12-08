#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct day2 {
    std::vector<int> low;
    std::vector<int> high;
    std::vector<char> c;
    std::vector<std::string> pw;
    int size = 0;
};
day2 get_data_day2(char* filename) {
    std::ifstream data_file(filename);
    day2 d;
    std::string buffer;
    while (std::getline(data_file, buffer)) {
        int low, high;
        char pw[100]{};
        char c;
        std::sscanf(buffer.c_str(), "%d-%d %1c: %s", &low, &high, &c, pw);
        d.low.push_back(low);
        d.high.push_back(high);
        d.c.push_back(c);
        d.pw.push_back(pw);
        d.size++;
    }
    return d;
}

auto main(int argc, char* argv[]) -> int {
    day2 d = get_data_day2(argv[1]);
    int ctr1 = 0;
    int ctr2 = 0;
    for (int i = 0; i < d.size; i++) {
        int occ = std::count(d.pw[i].begin(), d.pw[i].end(), d.c[i]);
        if (occ >= d.low[i] && d.high[i] >= occ)
            ctr1++;

        bool valid = false;
        if (d.pw[i][d.low[i] - 1] == d.c[i])
            valid = !valid;
        if (d.pw[i][d.high[i] - 1] == d.c[i])
            valid = !valid;
        if (valid)
            ctr2++;
    }
    std::cout << "ctr1: " << ctr1 << std::endl;
    std::cout << "ctr2: " << ctr2 << std::endl;
    return 0;
}
