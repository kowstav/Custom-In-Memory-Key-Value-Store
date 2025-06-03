#include "../include/lru_cache.hpp"
#include <iostream>
#include <cassert>

// Main function for testing LRUCache.
int main() {
    // Print start message for LRUCache tests.
    std::cout << "Running LRUCache Tests..." << std::endl;

    // Create an LRUCache instance with capacity 2.
    LRUCache cache(2);

    // Test 1: Initial size.
    assert(cache.size() == 0);
    // Print pass message for test 1.
    std::cout << "Test 1 (initial size) PASSED." << std::endl;

    // Test 2: Put and Get.
    cache.put("k1", "v1");
    // Assert that cache size is now 1.
    assert(cache.size() == 1);
    // Assert that getting "k1" returns "v1".
    assert(cache.get("k1") == "v1");
    // Print pass message for test 2.
    std::cout << "Test 2 (put/get basic) PASSED." << std::endl;

    // Test 3: Put another item, still within capacity.
    cache.put("k2", "v2");
    // Assert that cache size is now 2.
    assert(cache.size() == 2);
    // Assert that getting "k2" returns "v2".
    assert(cache.get("k2") == "v2");
    // Print pass message for test 3.
    std::cout << "Test 3 (put second item) PASSED." << std::endl;

    // Test 4: LRU Eviction. k1 should be LRU after getting k2.
    cache.get("k1"); // k1 is now MRU, k2 is LRU
    // Put k3, which should evict k2.
    cache.put("k3", "v3");
    // Assert that cache size is still 2 (capacity).
    assert(cache.size() == 2);
    // Assert that getting "k3" returns "v3".
    assert(cache.get("k3") == "v3");
    // Assert that getting "k2" (evicted) returns empty string.
    assert(cache.get("k2") == ""); // k2 should be evicted
    // Assert that k1 is still in cache.
    assert(cache.get("k1") == "v1");
    // Print pass message for test 4.
    std::cout << "Test 4 (LRU eviction) PASSED." << std::endl;

    // Test 5: Update existing key.
    cache.put("k1", "v1_updated");
    // Assert that cache size is still 2.
    assert(cache.size() == 2);
    // Assert that getting "k1" returns updated value.
    assert(cache.get("k1") == "v1_updated"); // k1 becomes MRU
    // Put k4, k3 should be evicted as it was LRU before k1's update.
    cache.put("k4", "v4");
    // Assert that getting "k3" returns empty string (evicted).
    assert(cache.get("k3") == "");
    // Assert that "k4" is present.
    assert(cache.get("k4") == "v4");
    // Print pass message for test 5.
    std::cout << "Test 5 (update existing key) PASSED." << std::endl;

    // Test 6: Get non-existent key.
    // Assert that getting "k5" (non-existent) returns empty string.
    assert(cache.get("k5") == "");
    // Print pass message for test 6.
    std::cout << "Test 6 (get non-existent) PASSED." << std::endl;

    // Test 7: Contains check
    assert(cache.contains("k1") == true);
    // Assert that cache does not contain "k3" (evicted).
    assert(cache.contains("k3") == false);
    // Print pass message for test 7.
    std::cout << "Test 7 (contains) PASSED." << std::endl;

    // Test 8: Remove key
    assert(cache.remove("k1") == true);
    // Assert that cache size is now 1.
    assert(cache.size() == 1);
    // Assert that "k1" is no longer contained.
    assert(cache.contains("k1") == false);
    // Assert that removing "k1" again returns false.
    assert(cache.remove("k1") == false);
    // Print pass message for test 8.
    std::cout << "Test 8 (remove key) PASSED." << std::endl;

    // Print completion message for LRUCache tests.
    std::cout << "All LRUCache Tests PASSED." << std::endl;
    // Return 0 indicating successful execution.
    return 0;
}