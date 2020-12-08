#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
/* Copy paste galore */
std::vector<std::string> get_data_day4(char* filename) {
    std::ifstream file(filename);
    std::vector<std::string> res;
    std::string line_buffer;
    std::string entry_buffer = "";
    while (std::getline(file, line_buffer)) {
        entry_buffer += " " + line_buffer;
        if (line_buffer.empty()) {
            res.push_back(entry_buffer);
            entry_buffer = "";
        }
    }
    res.push_back(entry_buffer);
    return res;
}

auto main(int argc, char* argv[]) -> int {
    std::cout << "**** DAY 4 ****\n";
    std::vector<std::string> d = get_data_day4(argv[1]);
    std::vector<std::string> valid;
    int ctr1 = 0;
    for (auto e : d) {
        if (e.find("byr:") != std::string::npos &&
            e.find("iyr:") != std::string::npos &&
            e.find("eyr:") != std::string::npos &&
            e.find("hgt:") != std::string::npos &&
            e.find("hcl:") != std::string::npos &&
            e.find("ecl:") != std::string::npos &&
            e.find("pid:") != std::string::npos) {
            ctr1++;
            valid.push_back(e);
        }
    }
    int ctr2 = 0;
    for (auto e : valid) {
        bool is_valid = true;
        std::string word;
        std::istringstream ss(e);
        while (getline(ss, word, ' ')) {
            if (word.find("byr:") != std::string::npos) {
                std::string s = word.substr(4);
                if (!(std::atoi(s.c_str()) >= 1920 &&
                      std::atoi(s.c_str()) <= 2002) ||
                    s.length() != 4) {
                    is_valid = false;
                    break;
                }
            } else if (word.find("iyr:") != std::string::npos) {
                std::string s = word.substr(4);
                if (!(std::atoi(s.c_str()) >= 2010 &&
                      std::atoi(s.c_str()) <= 2020) ||
                    s.length() != 4) {
                    is_valid = false;
                    break;
                }
            } else if (word.find("eyr:") != std::string::npos) {
                std::string s = word.substr(4);
                if (!(std::atoi(s.c_str()) >= 2020 &&
                      std::atoi(s.c_str()) <= 2030) ||
                    s.length() != 4) {
                    is_valid = false;
                    break;
                }
            } else if (word.find("hgt:") != std::string::npos) {
                if (word.length() != 9 && word.length() != 8) {
                    is_valid = false;
                    break;
                }
                if (word.substr(4 + 3, 2) == "cm") {
                    if (!(std::atoi(word.substr(4, 3).c_str()) >= 150 &&
                          std::atoi(word.substr(4, 3).c_str()) <= 193)) {
                        is_valid = false;
                        break;
                    }
                } else if (word.substr(4 + 2, 2) == "in") {
                    if (!(std::atoi(word.substr(4, 2).c_str()) >= 59 &&
                          std::atoi(word.substr(4, 2).c_str()) <= 76)) {
                        is_valid = false;
                        break;
                    }
                } else {
                    is_valid = false;
                    break;
                }
            } else if (word.find("hcl:") != std::string::npos) {
                if (!std::regex_search(
                        word.substr(4),
                        std::regex(
                            "^\\#(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})")) ||
                    word.length() != 11) {
                    is_valid = false;
                    break;
                }
            } else if (word.find("ecl:") != std::string::npos) {
                auto ecl = word.substr(4);
                if (!(ecl == "amb" || ecl == "blu" || ecl == "brn" ||
                      ecl == "gry" || ecl == "grn" || ecl == "hzl" ||
                      ecl == "oth")) {
                    is_valid = false;
                    break;
                }
            } else if (word.find("pid:") != std::string::npos) {
                if (!std::regex_search(word.substr(4), std::regex("\\d{9}")) ||
                    word.length() != 9 + 4) {
                    is_valid = false;
                    break;
                }
            }
        }
        if (is_valid) {
            ctr2++;
        }
    }
    std::cout << "ctr1: " << ctr1 << std::endl;
    std::cout << "ctr2: " << ctr2 << std::endl;
    return 0;
}
