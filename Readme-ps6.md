# PS6: RandWriter

## Contact
Name: Aanya Bharti
Section: 203
Time to Complete: 5 hours

## Description
This project implements a Markov text model of order k using a `RandWriter` class.
The program analyzes an input text, counts how often each k-gram appears, and records which characters follow each k-gram. It then uses those frequencies to randomly generate new text that statistically resembles the original input.

The project also includes a client program called `TextWriter` that reads `k` and `L` from the command line, reads source text from standard input, builds the Markov model, and prints a generated string of length `L`.

Functionality status: fully works.

### Features
The main data structure is a nested map:
- `map<string, int>` stores the total frequency of each k-gram
- `map<string, map<char, int>>` stores how many times each character follows a given k-gram

The constructor processes the text as a **circular string**, meaning the first `k` characters are treated as following the end of the text. This avoids dead ends during generation.

The `kRand()` method selects the next character with probability proportional to its observed frequency after the given k-gram. For example, if one letter followed a k-gram 5 times and another followed it 2 times, the first letter is more likely to be chosen.

The `generate()` method begins with the given seed k-gram and repeatedly uses the most recent `k` characters to choose the next character until the requested length is reached.

### Testing
I wrote Boost unit tests for:
- constructor and `orderK()`
- both `freq()` methods
- invalid k-gram length exceptions
- missing k-gram exception in `kRand()`
- order-0 behavior
- generated string length
- whether generated characters come from the valid set of followers

I used:
- `BOOST_REQUIRE`
- `BOOST_REQUIRE_THROW`
- `BOOST_REQUIRE_NO_THROW`

The code passes the tests I wrote.

### Lambda
I used a lambda expression inside `kRand()` with `std::find_if()`.
The lambda keeps a running cumulative frequency and returns `true` when the randomly selected target value falls into that character’s frequency range. This is how the program picks a character with the correct weighted probability.

### Issues
One of the harder parts was handling the circular text correctly. I had to make sure that the last k-gram in the text wraps around and uses characters from the beginning of the text.

Another tricky part was making `kRand()` use the correct weighted probabilities instead of choosing uniformly from the possible next characters.

I also had to be careful with the order-0 case, because the k-gram is the empty string and `freq("")` should return the full text length.

### Extra Credit (+3)
I implemented a WordWriter version of the program that generates text using words instead of characters.
The program splits input text into words using string streams and builds a Markov model based on sequences of words (k-grams). The same probabilistic approach is used to generate new text, but transitions occur between words rather than characters.
This produces more readable output compared to the character-based model.

## Acknowledgements
- Instructor / TAs
- Course handout / PS6 PDF
- Boost Test documentation
- C++ reference pages for `std::map`, `std::mt19937`, and `std::uniform_int_distribution`