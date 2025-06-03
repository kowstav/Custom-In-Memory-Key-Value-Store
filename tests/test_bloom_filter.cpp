#include "../include/bloom_filter.hpp"
#include <iostream>
#include <cassert>

// Main function for testing BloomFilter.
int main() {
    // Print start message for BloomFilter tests.
    std::cout << "Running BloomFilter Tests..." << std::endl;

    // Create a BloomFilter instance: size 100, 3 hash functions.
    BloomFilter filter(100, 3);

    // Test 1: Add a key and check if it possibly contains.
    filter.add("apple");
    // Assert that "apple" might be contained.
    assert(filter.possiblyContains("apple") == true);
    // Print pass message for test 1.
    std::cout << "Test 1 (add/possiblyContains basic) PASSED." << std::endl;

    // Test 2: Check for a key not added.
    bool bananaPossiblyExists = filter.possiblyContains("banana");
    // Print info about "banana" check.
    std::cout << "Info: 'banana' possiblyContains result: " << (bananaPossiblyExists ? "true (potential false positive or collision)" : "false") << std::endl;
    // Test 3: Add multiple keys.
    filter.add("banana"); // Now add banana
    // Add "cherry".
    filter.add("cherry");
    // Assert that "banana" now possibly exists.
    assert(filter.possiblyContains("banana") == true);
    // Assert that "cherry" now possibly exists.
    assert(filter.possiblyContains("cherry") == true);
    // Print pass message for test 3.
    std::cout << "Test 3 (add multiple) PASSED." << std::endl;

    // Test 4: Check a key definitely not present (if one of its hash bits is 0).
    bool datePossiblyExists = filter.possiblyContains("date");
    // Print info about "date" check.
    std::cout << "Info: 'date' possiblyContains result: " << (datePossiblyExists ? "true (potential false positive)" : "false (definitely not present)") << std::endl;
    // Print completion message for BloomFilter tests.
    std::cout << "BloomFilter Tests completed (interpret results considering probabilistic nature)." << std::endl;
    // Return 0 indicating successful execution.
    return 0;
}