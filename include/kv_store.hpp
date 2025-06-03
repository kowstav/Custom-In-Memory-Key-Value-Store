#ifndef KV_STORE_HPP
#define KV_STORE_HPP

#include "hash_map.hpp"
#include "trie.hpp"
#include "lru_cache.hpp"
#include "bloom_filter.hpp"
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr

// High-level interface for the In-Memory Key-Value Store.
class KVStore {
private:
    // The primary key-value storage.
    HashMap mainStore;
    // Trie for prefix searches on keys.
    Trie keyTrie;
    // LRU Cache for frequently accessed items.
    LRUCache cache; // LRU cache for values
    // Bloom Filter for fast "key not found" checks.
    BloomFilter filter;

    // Configuration for LRU cache capacity.
    static const size_t DEFAULT_CACHE_CAPACITY = 100;
    // Configuration for Bloom filter size.
    static const size_t DEFAULT_BLOOM_FILTER_SIZE = 1000;
    // Configuration for Bloom filter number of hash functions.
    static const size_t DEFAULT_BLOOM_FILTER_HASHES = 3;


public:
    // Constructor: initializes all underlying data structures.
    KVStore(size_t hashMapCapacity = 101,
            size_t cacheCapacity = DEFAULT_CACHE_CAPACITY,
            size_t bloomFilterSize = DEFAULT_BLOOM_FILTER_SIZE,
            size_t bloomFilterNumHashes = DEFAULT_BLOOM_FILTER_HASHES);

    // Sets (inserts or updates) a key-value pair in the store.
    void set(const std::string& key, const std::string& value);
    // Gets the value associated with a key.
    // Checks cache first, then main store. Updates LRU and access history.
    std::string get(const std::string& key);
    // Deletes a key from the store, cache, trie, and potentially bloom filter (conceptually, BF doesn't support true delete).
    bool remove(const std::string& key);
    // Retrieves all keys starting with the given prefix.
    std::vector<std::string> prefixSearch(const std::string& prefix);
    // Checks if a key might exist using the Bloom Filter.
    bool mightContain(const std::string& key);
};

#endif // KV_STORE_HPP