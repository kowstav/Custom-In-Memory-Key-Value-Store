#include "../include/kv_store.hpp"

// Constructor: initializes all underlying data structures.
KVStore::KVStore(size_t hashMapCapacity,
                 size_t cacheCapacity,
                 size_t bloomFilterSize,
                 size_t bloomFilterNumHashes)
    // Initialize mainStore with provided or default capacity.
    : mainStore(hashMapCapacity),
      // Initialize keyTrie (default constructor).
      keyTrie(), // Default constructor is fine
      // Initialize cache with provided or default capacity.
      cache(cacheCapacity),
      // Initialize filter with provided or default size and number of hashes.
      filter(bloomFilterSize, bloomFilterNumHashes) {
    // Constructor body can be empty if all initialization is done in the member initializer list.
}

// Sets (inserts or updates) a key-value pair in the store.
void KVStore::set(const std::string& key, const std::string& value) {
    // Set the key-value pair in the main hash map.
    mainStore.set(key, value);
    // Insert the key into the Trie for prefix searching.
    keyTrie.insert(key); // Assuming Trie's insert handles duplicates gracefully or is idempotent.
    // Add/update the key-value pair in the LRU cache.
    cache.put(key, value);
    // Add the key to the Bloom Filter.
    filter.add(key);
}

// Gets the value associated with a key.
std::string KVStore::get(const std::string& key) {
    // First, check the Bloom Filter to quickly rule out non-existent keys.
    if (!filter.possiblyContains(key)) {
        // If Bloom Filter says key is not present, it's definitively not.
        return ""; // Key definitely not found
    }

    // Try to get the value from the LRU cache.
    std::string cachedValue = cache.get(key);
    // If the value was found in the cache.
    if (!cachedValue.empty() || cache.contains(key)) { // `contains` check for empty string values
        // Return the cached value. LRU `get` already updated its recency.
        return cachedValue;
    }

    // If not in cache, get from the main store.
    std::string storeValue = mainStore.get(key);
    // If the value was found in the main store.
    if (!storeValue.empty() || mainStore.contains(key)) { // `contains` check for empty string values
        // Put the retrieved value into the cache for future accesses.
        cache.put(key, storeValue);
        // Return the value from the store.
        return storeValue;
    }
    // Key not found in main store either (Bloom filter might have given a false positive).
    return "";
}

// Deletes a key from the store, cache, trie.
bool KVStore::remove(const std::string& key) {
    // Check Bloom Filter first.
    if (!filter.possiblyContains(key)) {
        // Key definitely not present.
        return false;
    }

    // Attempt to remove from the main store.
    bool removedFromStore = mainStore.remove(key);
    // If key was successfully removed from the main store.
    if (removedFromStore) {
        // Remove the key from the Trie.
        keyTrie.remove(key);
        // Remove the key from the LRU cache.
        cache.remove(key);
    }
    // Return the status of removal from the main store.
    return removedFromStore;
}

// Retrieves all keys starting with the given prefix.
std::vector<std::string> KVStore::prefixSearch(const std::string& prefix) {
    // Perform prefix search using the Trie.
    return keyTrie.searchPrefix(prefix);
}

// Checks if a key might exist using the Bloom Filter.
bool KVStore::mightContain(const std::string& key) {
    // Query the Bloom Filter.
    return filter.possiblyContains(key);
}