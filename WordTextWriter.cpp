// Copyright 2026 Aanya Bharti

#include "WordWriter.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    size_t k = std::stoul(argv[1]);
    size_t L = std::stoul(argv[2]);

    std::ostringstream buffer;
    buffer << std::cin.rdbuf();
    std::string text = buffer.str();

    WordWriter ww(text, k);

    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string w;
    while (iss >> w) words.push_back(w);

    std::vector<std::string> seed(words.begin(), words.begin() + k);

    auto result = ww.generate(seed, L);

    for (const auto& word : result) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
