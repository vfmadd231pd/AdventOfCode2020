#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <unordered_map>
#include <vector>
typedef std::unordered_map<std::string, int> bag;
typedef std::unordered_map<std::string, bag> bags;
std::vector<std::string> split(const std::string& s, const std::regex& rgx) {
    std::vector<std::string> res;
    std::regex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    while (iter != std::sregex_token_iterator()) {
        res.push_back(iter++->str());
    }
    return res;
}
int part1(bags& bs, bag& b, const std::string& name) {
    if (b.find(name) != b.end())
        return 1;
    for (auto& _b : b) {
        if (part1(bs, bs[_b.first], name))
            return 1;
    }
    return 0;
}
int part2(bags& bs, bag& b, const std::string& name) {
    int sum = 0;
    for (auto& _b : b) {
        sum += _b.second + _b.second * part2(bs, bs[_b.first], name);
    }
    return sum;
}

auto main(int argc, char* argv[]) -> int {
    std::ifstream file(argv[1]);
    std::string l;
    bags bs;
    while (std::getline(file, l)) {
        auto vs = split(l, std::regex("(contain|,)"));
        std::string name;
        name = vs[0].substr(0, vs[0].length() - 2);
        bag _b;
        for_each(vs.begin() + 1, vs.end(), [&_b](auto b) {
            if (b.substr(1) != "no other bags.") {
                if (b[b.length() - 1] == '.')
                    b = b.substr(0, b.length() - 1);
                if (b[b.length() - 1] == 's')
                    b = b.substr(0, b.length() - 1);
                _b[b.substr(3)] = std::stoi(b.substr(1, 1));
            }
        });
        bs[name] = _b;
    }
    int ctr1 = 0;
    for (auto& b : bs) {
        ctr1 += part1(bs, b.second, "shiny gold bag");
    }

    std::cout << "Part1: " << ctr1 << std::endl;
    std::cout << "Part2: " << part2(bs, bs["shiny gold bag"], "shiny gold bag")
              << std::endl;
    return 0;
}
