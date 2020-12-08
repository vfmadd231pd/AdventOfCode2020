#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
class HGC {
  public:
    std::stack<std::unordered_map<int64_t, bool>> visited;
    int64_t acc = 0;
    int64_t inp = 0;
    std::stack<std::pair<int64_t, int64_t>> jnops;
    std::vector<std::pair<std::string, int64_t>> memory;
    int64_t last = 0;
    bool unwind = false;
    void ACC() {
        visited.top()[inp] = true;
        acc += memory[inp].second;
        inp++;
    }
    void JMP() {
        if (!unwind) {
            visited.push(visited.top());
            jnops.push(std::make_pair(inp, acc));
        }
        visited.top()[inp] = true;
        inp += memory[inp].second;
    }
    void NOP() {
        if (!unwind) {
            jnops.push(std::make_pair(inp, acc));
            visited.push(visited.top());
        }
        visited.top()[inp] = true;
        inp++;
    }

    void run() {
        for (;;) {
            if (visited.top().find(inp) != visited.top().end()) {
                if (unwind) {
                    if (memory[last].first == "jmp") {
                        memory[last].first = "nop";
                    } else if (memory[last].first == "nop") {
                        memory[last].first = "jmp";
                    }
                }
                acc = jnops.top().second;
                inp = jnops.top().first;
                last = inp;
                if (memory[inp].first == "jmp") {
                    memory[inp].first = "nop";
                } else if (memory[inp].first == "nop") {
                    memory[inp].first = "jmp";
                }
                jnops.pop();
                visited.pop();
                unwind = true;
            }
            if (inp >= memory.size()) {
                std::cout << "inp, acc: " << inp << ", " << acc << std::endl;
                break;
            }
            auto op = memory[inp];
            if (std::get<0>(op) == "acc") {
                ACC();
            } else if (std::get<0>(op) == "jmp") {
                JMP();
            } else if (std::get<0>(op) == "nop") {
                NOP();
            }
        }
    }
    HGC() = delete;
    HGC(std::vector<std::pair<std::string, int64_t>> mem) : memory(mem) {
        visited.push(std::unordered_map<int64_t, bool>());
    }
};
auto main(int argc, char* argv[]) -> int {
    std::cout << "*** DAY 8 ***" << std::endl;
    std::ifstream file(argv[1]);
    std::string buffer;
    std::vector<std::pair<std::string, int64_t>> data;
    while (std::getline(file, buffer)) {
        data.push_back(
            std::make_pair(buffer.substr(0, 3), std::stoi(buffer.substr(3))));
    }
    HGC hgc(data);
    hgc.run();
    return 0;
}
