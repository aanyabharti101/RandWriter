// Copyright 2026 Aanya Bharti

#include "RandWriter.hpp"

#include <set>
#include <stdexcept>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RandWriterTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_orderK_constructor) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    BOOST_REQUIRE_EQUAL(rw.orderK(), 2UL);
}

BOOST_AUTO_TEST_CASE(test_freq_kgram) {
    RandWriter rw("ABRACADABRA", 1);

    BOOST_REQUIRE_EQUAL(rw.freq("A"), 5);
    BOOST_REQUIRE_EQUAL(rw.freq("B"), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("R"), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("Z"), 0);
}

BOOST_AUTO_TEST_CASE(test_freq_kgram_char) {
    RandWriter rw("ABRACADABRA", 1);

    BOOST_REQUIRE_EQUAL(rw.freq("A", 'B'), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("A", 'C'), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("A", 'D'), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("A", 'A'), 1);  // circular wrap
    BOOST_REQUIRE_EQUAL(rw.freq("B", 'R'), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("Z", 'Q'), 0);
}

BOOST_AUTO_TEST_CASE(test_invalid_kgram_exceptions) {
    RandWriter rw("banana", 2);

    BOOST_REQUIRE_THROW(rw.freq("a"), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.freq("abc"), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.freq("a", 'n'), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.kRand("a"), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.generate("a", 10), std::invalid_argument);

    BOOST_REQUIRE_NO_THROW(rw.freq("ba"));
    BOOST_REQUIRE_NO_THROW(rw.freq("ba", 'n'));
    BOOST_REQUIRE_NO_THROW(rw.kRand("ba"));
    BOOST_REQUIRE_NO_THROW(rw.generate("ba", 10));
}

BOOST_AUTO_TEST_CASE(test_kRand_returns_valid_followers) {
    RandWriter rw("banana", 2);

    BOOST_REQUIRE_EQUAL(rw.kRand("ba"), 'n');

    for (int i = 0; i < 50; ++i) {
        char c1 = rw.kRand("an");
        BOOST_REQUIRE(c1 == 'a');

        char c2 = rw.kRand("na");
        BOOST_REQUIRE(c2 == 'n' || c2 == 'b');
    }
}

BOOST_AUTO_TEST_CASE(test_kRand_missing_kgram_exception) {
    RandWriter rw("banana", 2);

    // FIXED: must expect invalid_argument (not runtime_error)
    BOOST_REQUIRE_THROW(rw.kRand("zz"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_generate_length_and_seed) {
    RandWriter rw("banana", 2);
    std::string out = rw.generate("ba", 10);

    BOOST_REQUIRE_EQUAL(out.size(), 10UL);
    BOOST_REQUIRE_EQUAL(out.substr(0, 2), "ba");
}

BOOST_AUTO_TEST_CASE(test_generate_uses_valid_characters) {
    RandWriter rw("banana", 2);
    std::string out = rw.generate("na", 20);

    BOOST_REQUIRE_EQUAL(out.size(), 20UL);

    std::set<char> allowed = {'a', 'b', 'n'};
    for (char c : out) {
        BOOST_REQUIRE(allowed.count(c) == 1);
    }
}

BOOST_AUTO_TEST_CASE(test_order_zero_model) {
    RandWriter rw("gagggagaggcgagaaa", 0);

    BOOST_REQUIRE_EQUAL(rw.orderK(), 0UL);
    BOOST_REQUIRE_EQUAL(rw.freq(""), 17);
    BOOST_REQUIRE_EQUAL(rw.freq("", 'a'), 7);
    BOOST_REQUIRE_EQUAL(rw.freq("", 'g'), 9);
    BOOST_REQUIRE_EQUAL(rw.freq("", 'c'), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("", 'z'), 0);

    BOOST_REQUIRE_NO_THROW(rw.kRand(""));
    std::string out = rw.generate("", 25);
    BOOST_REQUIRE_EQUAL(out.size(), 25UL);
}
