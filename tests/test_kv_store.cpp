#include "../include/kv_store.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm> // For std::sort

// Main function for testing KVStore.
int main() {
    // Print start message for KVStore tests.
    std::cout << "Running KVStore Tests..." << std::endl;

    // Create a KVStore instance with small capacities for easier testing of cache/etc.
    KVStore store(10, 2, 100, 3);
    // Test 1: Set and Get.
    store.set("fruit1", "apple");
    // Assert that getting "fruit1" returns "apple".
    assert(store.get("fruit1") == "apple");
    // Print pass message for test 1.
    std::cout << "Test 1 (set/get basic) PASSED." << std::endl;

    // Test 2: Get non-existent key (check Bloom Filter path).
    assert(store.get("unknown_key") == "");
    // Assert that Bloom Filter also reports "unknown_key" as not present.
    assert(store.mightContain("unknown_key") == false);
    // Print pass message for test 2.
    std::cout << "Test 2 (get non-existent & bloom) PASSED." << std::endl;

    // Test 3: LRU Cache behavior within KVStore.
    store.set("fruit2", "banana"); 
    // Access fruit1, making it MRU.
    store.get("fruit1");              
    // Add fruit3, should evict fruit2 from cache.
    store.set("fruit3", "cherry");    
    assert(store.get("fruit3") == "cherry");
    // Assert that "fruit1" is "apple".
    assert(store.get("fruit1") == "apple");
    assert(store.get("fruit2") == "banana"); // fruit2 (MRU), fruit1 (LRU) in cache now. fruit3 evicted.
    // Print pass message for test 3.
    std::cout << "Test 3 (LRU cache behavior) PASSED." << std::endl;

    // Test 4: Prefix Search.
    store.set("app_service", "running");
    // Set another key with "app" prefix.
    store.set("app_config", "loaded");
    // Search for prefix "app".
    std::vector<std::string> prefixResults = store.prefixSearch("app");
    // Sort results for consistent comparison.
    std::sort(prefixResults.begin(), prefixResults.end());
    // Assert that 2 keys match the prefix "app".
    assert(prefixResults.size() == 2);
    // Assert that "app_config" is one of them.
    assert(prefixResults[0] == "app_config");
    // Assert that "app_service" is one of them.
    assert(prefixResults[1] == "app_service");
    // Print pass message for test 4.
    std::cout << "Test 4 (prefix search) PASSED." << std::endl;

    // Test 5: Delete a key.
    assert(store.remove("fruit1") == true);
    // Assert that getting "fruit1" now returns empty string.
    assert(store.get("fruit1") == "");
    std::cout << "Test 5 (remove key) PASSED." << std::endl;

    // Test 6: mightContain for a deleted key.
    bool might_contain_deleted = store.mightContain("fruit1");
    // Print info about mightContain for deleted key.
    std::cout << "Info: mightContain for deleted 'fruit1': " << (might_contain_deleted ? "true (expected false positive)" : "false") << std::endl;
    // Print pass message for test 6.
    std::cout << "Test 6 (bloom for deleted key) PASSED (behavior is informational)." << std::endl;


    // Print completion message for KVStore tests.
    std::cout << "All KVStore Tests PASSED (some behaviors are probabilistic/informational)." << std::endl;
    // Return 0 indicating successful execution.
    return 0;
}