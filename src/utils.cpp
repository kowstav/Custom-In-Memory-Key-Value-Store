#include "../include/utils.hpp"

// Contains utility functions, like hash functions for the Bloom filter.
namespace Utils {

    // First hash function for Bloom Filter (example: simple variant of DJB2).
    unsigned int hashFunction1(const std::string& key) {
        // Initialize hash value.
        unsigned int hash = 5381;
        // Iterate through each character of the key.
        for (char c : key) {
            // Update hash: hash * 33 + c.
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        // Return the computed hash.
        return hash;
    }

    // Second hash function for Bloom Filter (example: SDBM hash).
    unsigned int hashFunction2(const std::string& key) {
        // Initialize hash value.
        unsigned int hash = 0;
        // Iterate through each character of the key.
        for (char c : key) {
            // Update hash: c + (hash << 6) + (hash << 16) - hash.
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        // Return the computed hash.
        return hash;
    }
    
    // Third hash function for Bloom Filter (example: a different multiplicative hash).
    unsigned int hashFunction3(const std::string& key) {
        // Initialize hash value.
        unsigned int hash = 0;
        // A prime number for multiplication.
        unsigned int prime = 31;
        // Iterate through each character of the key.
        for (char c : key) {
            // Update hash: (hash * prime) + c.
            hash = (hash * prime) + c;
        }
        // Return the computed hash.
        return hash;
    }
}