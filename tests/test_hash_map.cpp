#include "../include/hash_map.hpp"
#include <iostream>
#include <cassert> // For basic assertions

// Main function for testing HashMap.
int main() {
    // Print start message for HashMap tests.
    std::cout << "Running HashMap Tests..." << std::endl;

    // Create a HashMap instance with capacity 5.
    HashMap map(5);

    // Test 1: Initial size should be 0.
    assert(map.size() == 0);
    // Print pass message for test 1.
    std::cout << "Test 1 (initial size) PASSED." << std::endl;

    // Test 2: Set and Get a key-value pair.
    map.set("apple", "red");
    // Assert that the value for "apple" is "red".
    assert(map.get("apple") == "red");
    // Assert that map size is now 1.
    assert(map.size() == 1);
    // Print pass message for test 2.
    std::cout << "Test 2 (set/get basic) PASSED." << std::endl;

    // Test 3: Update an existing key.
    map.set("apple", "green");
    // Assert that the value for "apple" is now "green".
    assert(map.get("apple") == "green");
    // Assert that map size is still 1 (update, not insert).
    assert(map.size() == 1);
    // Print pass message for test 3.
    std::cout << "Test 3 (update key) PASSED." << std::endl;

    // Test 4: Get a non-existent key.
    assert(map.get("banana") == "");
    // Print pass message for test 4.
    std::cout << "Test 4 (get non-existent) PASSED." << std::endl;

    // Test 5: Set multiple keys (check for collisions if capacity is small).
    map.set("banana", "yellow");
    // Assert that the value for "banana" is "yellow".
    assert(map.get("banana") == "yellow");
    // Assert that map size is now 2.
    assert(map.size() == 2);
    // Set another key.
    map.set("cherry", "red");
    // Assert that value for "cherry" is "red".
    assert(map.get("cherry") == "red");
    // Assert that map size is now 3.
    assert(map.size() == 3);
    // Print pass message for test 5.
    std::cout << "Test 5 (set multiple) PASSED." << std::endl;

    // Test 6: Remove an existing key.
    assert(map.remove("apple") == true);
    // Assert that map size is now 2.
    assert(map.size() == 2);
    // Assert that getting "apple" now returns empty string.
    assert(map.get("apple") == "");
    // Print pass message for test 6.
    std::cout << "Test 6 (remove existing) PASSED." << std::endl;

    // Test 7: Remove a non-existent key.
    assert(map.remove("grape") == false);
    // Assert that map size is still 2.
    assert(map.size() == 2);
    // Print pass message for test 7.
    std::cout << "Test 7 (remove non-existent) PASSED." << std::endl;

    // Test 8: Contains check.
    assert(map.contains("banana") == true);
    // Assert that map does not contain "apple" (removed).
    assert(map.contains("apple") == false);
    // Print pass message for test 8.
    std::cout << "Test 8 (contains) PASSED." << std::endl;


    // Print completion message for HashMap tests.
    std::cout << "All HashMap Tests PASSED." << std::endl;
    // Return 0 indicating successful execution of tests.
    return 0;
}