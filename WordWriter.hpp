// Copyright 2026 Aanya Bharti

#ifndef WORDWRITER_HPP
#define WORDWRITER_HPP

#include <map>
#include <random>
#include <string>
#include <vector>

class WordWriter {
 public:
    WordWriter(const std::string& text, size_t k);

    size_t orderK() const;

    int freq(const std::vector<std::string>& kgram) const;

    int freq(const std::vector<std::string>& kgram,
             const std::string& word) const;

    std::string kRand(const std::vector<std::string>& kgram);

    std::vector<std::string> generate(
        const std::vector<std::string>& kgram, size_t L);

 private:
    size_t k_;
    std::vector<std::string> words_;

    std::map<std::vector<std::string>, int> kgram_freq_;
    std::map<std::vector<std::string>,
             std::map<std::string, int>> next_freq_;

    std::mt19937 gen_;

    void validateKgram(const std::vector<std::string>& kgram) const;
};

#endif  // WORDWRITER_HPP
