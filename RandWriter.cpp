// Copyright 2026 Aanya Bharti

#include "RandWriter.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

RandWriter::RandWriter(const std::string& str, size_t k)
    : k_(k), text_(str) {
    if (text_.size() < k_) {
        throw std::invalid_argument("text length must be at least k");
    }

    const auto seed = static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count());
    gen_ = std::mt19937(seed);

    std::set<char> alphabet_set;
    for (char ch : text_) {
        alphabet_set.insert(ch);
    }
    alphabet_.assign(alphabet_set.begin(), alphabet_set.end());

    const size_t n = text_.size();

    if (k_ == 0) {
        for (size_t i = 0; i < n; ++i) {
            const std::string kgram = "";
            const char next = text_[i];
            ++kgram_freq_[kgram];
            ++next_freq_[kgram][next];
        }
        return;
    }

    const std::string extended = text_ + text_.substr(0, k_);

    for (size_t i = 0; i < n; ++i) {
        const std::string kgram = extended.substr(i, k_);
        const char next = extended[i + k_];
        ++kgram_freq_[kgram];
        ++next_freq_[kgram][next];
    }
}

size_t RandWriter::orderK() const {
    return k_;
}

void RandWriter::validateKgram(const std::string& kgram) const {
    if (kgram.size() != k_) {
        throw std::invalid_argument("kgram is not of length k");
    }
}

int RandWriter::freq(const std::string& kgram) const {
    validateKgram(kgram);

    auto it = kgram_freq_.find(kgram);
    if (it == kgram_freq_.end()) {
        return 0;
    }
    return it->second;
}

int RandWriter::freq(const std::string& kgram, char c) const {
    validateKgram(kgram);

    auto outer = next_freq_.find(kgram);
    if (outer == next_freq_.end()) {
        return 0;
    }

    auto inner = outer->second.find(c);
    if (inner == outer->second.end()) {
        return 0;
    }
    return inner->second;
}

char RandWriter::kRand(const std::string& kgram) {
    validateKgram(kgram);

    auto it = next_freq_.find(kgram);
    if (it == next_freq_.end() || it->second.empty()) {
        throw std::runtime_error("no such kgram");
    }

    int total = 0;
    for (const auto& entry : it->second) {
        total += entry.second;
    }

    if (total <= 0) {
        throw std::runtime_error("no such kgram");
    }

    std::uniform_int_distribution<int> dist(1, total);
    const int target = dist(gen_);

    int running = 0;
    auto found = std::find_if(it->second.begin(), it->second.end(),
        [target, &running](const std::pair<const char, int>& entry) {
            running += entry.second;
            return target <= running;
        });

    if (found == it->second.end()) {
        throw std::runtime_error("random selection failed");
    }

    return found->first;
}

std::string RandWriter::generate(const std::string& kgram, size_t l) {
    validateKgram(kgram);

    if (l < k_) {
        throw std::invalid_argument("L must be at least k");
    }

    if (k_ == 0) {
        std::string result;
        result.reserve(l);
        for (size_t i = 0; i < l; ++i) {
            result += kRand("");
        }
        return result;
    }

    std::string result = kgram;
    while (result.size() < l) {
        const std::string current = result.substr(result.size() - k_, k_);
        result += kRand(current);
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const RandWriter& rw) {
    out << "Order: " << rw.k_ << '\n';
    out << "Alphabet: " << rw.alphabet_ << '\n';
    out << "k-gram frequencies:\n";

    for (const auto& entry : rw.kgram_freq_) {
        out << "  \"" << entry.first << "\" : " << entry.second << '\n';
    }

    out << "k+1-gram frequencies:\n";
    for (const auto& outer : rw.next_freq_) {
        for (const auto& inner : outer.second) {
            out << "  \"" << outer.first << inner.first
                << "\" : " << inner.second << '\n';
        }
    }

    return out;
}
