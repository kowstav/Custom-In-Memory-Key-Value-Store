#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <string>
#include <vector>
#include <functional> // For std::function

// Implements a Bloom Filter for probabilistic checking of key existence.
class BloomFilter {
private:
    // The bit array representing the Bloom Filter.
    std::vector<bool> bitArray;
    // The size of the bit array.
    size_t arraySize;
    // The number of hash functions to use.
    size_t numHashFunctions;
    // Vector of hash functions. Each takes a string and returns an unsigned int.
    std::vector<std::function<unsigned int(const std::string&)>> hashFunctions;


public:
    // Constructor: initializes the Bloom Filter with a given size and number of hash functions.
    BloomFilter(size_t size, size_t numHashes);

    // Adds a key to the Bloom Filter.
    void add(const std::string& key);
    // Checks if a key might exist in the set.
    bool possiblyContains(const std::string& key) const;
};

#endif // BLOOM_FILTER_HPP