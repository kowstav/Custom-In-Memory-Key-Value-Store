#include "../include/bloom_filter.hpp"
#include "../include/utils.hpp" // For Utils::hashFunction1, etc.

// Constructor: initializes the Bloom Filter with a given size and number of hash functions.
BloomFilter::BloomFilter(size_t size, size_t numHashes)
    : arraySize(size), numHashFunctions(numHashes) {
    // Resize the bit array to the specified size and initialize all bits to false.
    bitArray.resize(arraySize, false);

    if (numHashes >= 1) {
        // Add first hash function.
        hashFunctions.push_back(Utils::hashFunction1);
    }
    // If at least two hash functions are requested.
    if (numHashes >= 2) {
        // Add second hash function.
        hashFunctions.push_back(Utils::hashFunction2);
    }
    // If at least three hash functions are requested.
    if (numHashes >= 3) {
        // Add third hash function.
        hashFunctions.push_back(Utils::hashFunction3);
    }
    // Ensure numHashFunctions does not exceed available hash functions.
    this->numHashFunctions = hashFunctions.size();
}


// Adds a key to the Bloom Filter.
void BloomFilter::add(const std::string& key) {
    // Iterate through each hash function.
    for (size_t i = 0; i < numHashFunctions; ++i) {
        // Compute the hash value for the key using the current hash function.
        unsigned int hashValue = hashFunctions[i](key) % arraySize;
        // Set the bit at the computed index to true.
        bitArray[hashValue] = true;
    }
}

// Checks if a key might exist in the set.
bool BloomFilter::possiblyContains(const std::string& key) const {
    // If the bit array is empty (e.g. size 0), nothing can be contained.
    if (arraySize == 0) return false;
    // Iterate through each hash function.
    for (size_t i = 0; i < numHashFunctions; ++i) {
        // Compute the hash value for the key.
        unsigned int hashValue = hashFunctions[i](key) % arraySize;
        // If the bit at the computed index is false.
        if (!bitArray[hashValue]) {
            // The key definitely does not exist.
            return false;
        }
    }
    // All corresponding bits are true, so the key might exist (could be a false positive).
    return true;
}