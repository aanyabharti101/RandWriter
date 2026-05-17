// Copyright 2026 Aanya Bharti

#include "WordWriter.hpp"

#include <chrono>
#include <sstream>
#include <stdexcept>

WordWriter::WordWriter(const std::string& text, size_t k) : k_(k) {
    std::istringstream iss(text);
    std::string w;
    while (iss >> w) {
        words_.push_back(w);
    }

    if (words_.size() < k_) {
        throw std::invalid_argument("not enough words");
    }

    gen_ = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

    size_t n = words_.size();

    std::vector<std::string> extended = words_;
    extended.insert(extended.end(), words_.begin(), words_.begin() + k_);

    for (size_t i = 0; i < n; i++) {
        std::vector<std::string> kgram(
            extended.begin() + i,
            extended.begin() + i + k_);

        std::string next = extended[i + k_];

        kgram_freq_[kgram]++;
        next_freq_[kgram][next]++;
    }
}

size_t WordWriter::orderK() const {
    return k_;
}

void WordWriter::validateKgram(
    const std::vector<std::string>& kgram) const {
    if (kgram.size() != k_) {
        throw std::invalid_argument("wrong kgram size");
    }
}

int WordWriter::freq(
    const std::vector<std::string>& kgram) const {
    validateKgram(kgram);

    auto it = kgram_freq_.find(kgram);
    if (it == kgram_freq_.end()) return 0;
    return it->second;
}

int WordWriter::freq(
    const std::vector<std::string>& kgram,
    const std::string& word) const {
    validateKgram(kgram);

    auto it = next_freq_.find(kgram);
    if (it == next_freq_.end()) return 0;

    auto inner = it->second.find(word);
    if (inner == it->second.end()) return 0;

    return inner->second;
}

std::string WordWriter::kRand(
    const std::vector<std::string>& kgram) {
    validateKgram(kgram);

    auto it = next_freq_.find(kgram);
    if (it == next_freq_.end()) {
        throw std::invalid_argument("unknown kgram");
    }

    int total = 0;
    for (auto& p : it->second) total += p.second;

    std::uniform_int_distribution<int> dist(1, total);
    int target = dist(gen_);

    int running = 0;
    for (auto& p : it->second) {
        running += p.second;
        if (target <= running) {
            return p.first;
        }
    }

    throw std::invalid_argument("random failed");
}

std::vector<std::string> WordWriter::generate(
    const std::vector<std::string>& kgram, size_t L) {
    validateKgram(kgram);

    if (L < k_) {
        throw std::invalid_argument("L too small");
    }

    std::vector<std::string> result = kgram;

    while (result.size() < L) {
        std::vector<std::string> current(
            result.end() - k_, result.end());

        result.push_back(kRand(current));
    }

    return result;
}
