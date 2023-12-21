#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>

unsigned long long part1(std::vector<std::string>& text);
unsigned long long part2(std::vector<std::string>& text);
int main(void) {
    std::ifstream input("input.txt", std::ios_base::in);
    if (input.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(input, line)) {
            lines.push_back(line);
        }
        std::cout << "Part 1 :" << part1(lines) << std::endl;
        std::cout << "Part 2 :" << part2(lines) << std::endl;
    }
    return(0);
}

unsigned long long part1(std::vector<std::string>& text)
{
    unsigned long long res = 0;
    for (auto s : text) {
        int num = 0;
        int curr = 0;
        for (int i = 0; s[i] != '\0';++i) {
            if (std::isdigit(s[i])) {
                curr = s[i] - '0';
                if (!num) num = curr;
            }
        }
        res += num * 10 + curr;
    }
    return res;
}
unsigned long long part2(std::vector<std::string>& text)
{
    static const std::unordered_map<std::string, int> words = { {"one", 1}, {"two", 2}, {"six", 6},{"four", 4}, {"five", 5}, {"nine", 9},{"three", 3}, {"seven", 7}, {"eight", 8}, };
    unsigned long long res = 0;
    for (auto s : text) {
        int num = 0;
        int curr = 0;
        for (int i = 0; s[i] != '\0';++i) {
            if (std::isdigit(s[i])) {
                curr = s[i] - '0';
                if (!num) num = curr;
            }
            else {
                for (auto& key : words) {
                    int size = key.first.size();
                    std::string sub = s.substr(i, size);
                    if (sub == key.first) {
                        curr = key.second;
                        if (!num) num = curr;
                    }
                }
            }
        }
        res += num * 10 + curr;
    }
    return res;
}