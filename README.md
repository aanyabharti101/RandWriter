# RandWriter

A probabilistic text generation engine written in C++ using Markov chain modeling and weighted random selection.

This project analyzes input text, builds a statistical model of character transitions using k-grams, and generates new text that mimics the structure and patterns of the original source material. The implementation uses circular Markov modeling, frequency-based prediction, STL containers, randomized generation, and automated Boost unit testing.

---

## Features

- Implements an order-k Markov text model
- Generates statistically similar text from source input
- Uses weighted random character selection based on observed frequencies
- Supports circular text wrapping to avoid dead-end states
- Handles arbitrary k-gram sizes
- Includes full Boost unit test coverage
- Built with modern C++20

---

## How It Works

The program scans an input text and records:

- how frequently each k-gram appears
- which characters follow each k-gram
- the probability distribution of possible next characters

Text generation begins with a seed k-gram and repeatedly predicts the next character using weighted probabilistic selection.

For example, if a character follows a k-gram more frequently in the source text, it is more likely to be generated.

The implementation uses:

- `std::map`
- `std::mt19937`
- `std::uniform_int_distribution`
- STL algorithms
- randomized weighted sampling

---

## Example

### Input

```bash
./TextWriter 3 500 < input17.txt
```
- `3` = the order-k value, meaning the generator uses the previous 3 characters to predict the next character
- `500` = total length of generated output
- `input17.txt` = source text used to build the Markov model

### Generated Output

```txt
gagggagaaagaaag...
```

The generated sequence statistically resembles the original source input while still producing randomized output.

---

## Project Structure

```txt
RandWriter.cpp
RandWriter.hpp
TextWriter.cpp
test.cpp
Makefile
```

### Core Components

| File | Purpose |
|---|---|
| `RandWriter.cpp` | Markov model implementation |
| `RandWriter.hpp` | Class definitions |
| `TextWriter.cpp` | Command-line client program |
| `test.cpp` | Boost unit tests |
| `Makefile` | Build automation |

---

## Testing

The project includes automated Boost unit tests covering:

- constructor behavior
- k-gram frequency counting
- weighted random generation
- exception handling
- order-0 models
- generated output validation
- invalid k-gram detection

---

## Algorithms & Concepts

- Markov chains
- Probabilistic text generation
- Frequency analysis
- Weighted random sampling
- Circular string modeling
- STL containers and iterators
- Random number generation
- Unit testing with Boost

---

## Extra Credit: WordWriter

An additional word-based Markov generator was implemented using sequences of words instead of characters.

This version generates more human-readable output by modeling probabilistic transitions between words rather than individual characters.

---

## Technologies

- C++20
- Boost Unit Test Framework
- SFML-compatible build environment
- GNU Make

---

## Author

Aanya Bharti  
Computer Science & Mathematics  
University of Massachusetts Lowell
