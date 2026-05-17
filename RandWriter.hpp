// Copyright 2026 Aanya Bharti

#ifndef RANDWRITER_HPP
#define RANDWRITER_HPP

#include <map>
#include <random>
#include <string>

class RandWriter {
 public:
    // Create a Markov model of order k from given text
    // Assume that text has length at least k.
    RandWriter(const std::string& str, size_t k);

    size_t orderK() const;

    // Number of occurrences of kgram in text
    // Throw an exception if kgram is not length k
    int freq(const std::string& kgram) const;

    // Number of times that character c follows kgram
    // if order=0, return num of times that char c appears
    // Throw an exception if kgram is not length k
    int freq(const std::string& kgram, char c) const;

    // Random character following given kgram
    // Throw an exception if kgram is not length k
    // Throw an exception if no such kgram
    char kRand(const std::string& kgram);

    // Generate a string of length L characters by simulating a trajectory
    // through the corresponding Markov chain. The first k characters of
    // the newly generated string should be the argument kgram.
    // Throw an exception if kgram is not length k.
    // Assume that L is at least k.
    std::string generate(const std::string& kgram, size_t l);

    friend std::ostream& operator<<(std::ostream& out, const RandWriter& rw);

 private:
    size_t k_;
    std::string text_;
    std::string alphabet_;

    // kgram -> total frequency
    std::map<std::string, int> kgram_freq_;

    // kgram -> (next char -> frequency)
    std::map<std::string, std::map<char, int>> next_freq_;

    std::mt19937 gen_;

    void validateKgram(const std::string& kgram) const;
};

#endif  // RANDWRITER_HPP
