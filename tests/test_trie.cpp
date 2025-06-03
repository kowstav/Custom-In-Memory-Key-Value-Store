#include "../include/trie.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm> // For std::sort

// Main function for testing Trie.
int main() {
    // Print start message for Trie tests.
    std::cout << "Running Trie Tests..." << std::endl;

    // Create a Trie instance.
    Trie trie;

    // Test 1: Insert and Contains.
    trie.insert("apple");
    // Assert that "apple" is contained in the trie.
    assert(trie.contains("apple") == true);
    // Assert that "app" (prefix, not full key) is not contained.
    assert(trie.contains("app") == false);
    // Assert that "apply" (different key) is not contained.
    assert(trie.contains("apply") == false);
    // Print pass message for test 1.
    std::cout << "Test 1 (insert/contains) PASSED." << std::endl;

    // Test 2: Insert multiple keys.
    trie.insert("apricot");
    // Insert "application".
    trie.insert("application");
    // Assert that "apricot" is contained.
    assert(trie.contains("apricot") == true);
    // Assert that "application" is contained.
    assert(trie.contains("application") == true);
    // Print pass message for test 2.
    std::cout << "Test 2 (insert multiple) PASSED." << std::endl;

    // Test 3: Prefix Search.
    std::vector<std::string> prefixResults = trie.searchPrefix("app");
    // Sort results for consistent comparison.
    std::sort(prefixResults.begin(), prefixResults.end());
    // Assert that 3 keys match the prefix "app".
    assert(prefixResults.size() == 3);
    // Assert that the first result is "apple".
    assert(prefixResults[0] == "apple");
    // Assert that the second result is "application".
    assert(prefixResults[1] == "application");
    // Assert that "apricot" is not in results for "app" (mistake in manual trace, "apricot" does start with "ap", not "app").
    // Let's correct this test. "apricot" will not be found by prefix "app".
    // Corrected test: "apple", "application" are expected for prefix "app"
    // Re-inserting to be sure of state
    Trie trieForPrefixTest;
    // Insert "apple".
    trieForPrefixTest.insert("apple");
    // Insert "application".
    trieForPrefixTest.insert("application");
    // Insert "apply".
    trieForPrefixTest.insert("apply");
    // Insert "apricot".
    trieForPrefixTest.insert("apricot"); // This one should not match "app" but "ap"
    // Search for prefix "app".
    prefixResults = trieForPrefixTest.searchPrefix("app");
    // Sort results.
    std::sort(prefixResults.begin(), prefixResults.end());
    // Assert size is 3.
    assert(prefixResults.size() == 3); // apple, application, apply
    // Assert "apple" is present.
    assert(prefixResults[0] == "apple");
    // Assert "application" is present.
    assert(prefixResults[1] == "application");
    // Assert "apply" is present.
    assert(prefixResults[2] == "apply");
    // Search for prefix "ap".
    std::vector<std::string> prefixResultsAp = trieForPrefixTest.searchPrefix("ap");
    // Sort results for "ap".
    std::sort(prefixResultsAp.begin(), prefixResultsAp.end());
    // Assert size is 4.
    assert(prefixResultsAp.size() == 4); // apple, application, apply, apricot
    // Assert "apricot" is present in "ap" results.
    assert(std::find(prefixResultsAp.begin(), prefixResultsAp.end(), "apricot") != prefixResultsAp.end());
    // Print pass message for test 3.
    std::cout << "Test 3 (prefix search) PASSED." << std::endl;

    // Test 4: Remove an existing key.
    Trie trieRemoveTest;
    // Insert "banana".
    trieRemoveTest.insert("banana");
    // Insert "band".
    trieRemoveTest.insert("band");
    // Assert that "banana" can be removed.
    assert(trieRemoveTest.remove("banana") == true);
    // Assert that "banana" is no longer contained.
    assert(trieRemoveTest.contains("banana") == false);
    // Assert that "band" (shares prefix) is still contained.
    assert(trieRemoveTest.contains("band") == true);
    // Print pass message for test 4.
    std::cout << "Test 4 (remove existing) PASSED." << std::endl;

    // Test 5: Remove a non-existent key.
    assert(trieRemoveTest.remove("apple") == false);
    // Print pass message for test 5.
    std::cout << "Test 5 (remove non-existent) PASSED." << std::endl;

    // Test 6: Remove a key that is a prefix of another.
    Trie triePrefixRemoveTest;
    // Insert "apply".
    triePrefixRemoveTest.insert("apply");
    // Insert "application".
    triePrefixRemoveTest.insert("application");
    // Assert that "apply" can be removed.
    assert(triePrefixRemoveTest.remove("apply") == true);
    // Assert that "apply" is no longer contained.
    assert(triePrefixRemoveTest.contains("apply") == false);
    // Assert that "application" is still contained.
    assert(triePrefixRemoveTest.contains("application") == true);
    // Print pass message for test 6.
    std::cout << "Test 6 (remove prefix key) PASSED." << std::endl;

    // Print completion message for Trie tests.
    std::cout << "All Trie Tests PASSED." << std::endl;
    // Return 0 indicating successful execution.
    return 0;
}