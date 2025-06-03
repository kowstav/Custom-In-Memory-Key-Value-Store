#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector> // For Bloom filter hash functions

// Contains utility functions, like hash functions for the Bloom filter.
namespace Utils {
    // First hash function for Bloom Filter (example: simple variant of DJB2).
    unsigned int hashFunction1(const std::string& key);
    // Second hash function for Bloom Filter (example: SDBM hash).
    unsigned int hashFunction2(const std::string& key);
    // Third hash function for Bloom Filter (example: a different multiplicative hash).
    unsigned int hashFunction3(const std::string& key);
}

#endif // UTILS_HPP