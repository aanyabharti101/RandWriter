// Copyright 2026 Aanya Bharti

#include "RandWriter.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./TextWriter k L\n";
        return 1;
    }

    try {
        const size_t k = static_cast<size_t>(std::stoul(argv[1]));
        const size_t L = static_cast<size_t>(std::stoul(argv[2]));

        std::ostringstream input_buffer;
        input_buffer << std::cin.rdbuf();
        const std::string text = input_buffer.str();

        if (text.size() < k) {
            throw std::invalid_argument("input text length must be at least k");
        }
        if (L < k) {
            throw std::invalid_argument("L must be at least k");
        }

        RandWriter rw(text, k);
        const std::string seed = text.substr(0, k);
        std::cout << rw.generate(seed, L) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
