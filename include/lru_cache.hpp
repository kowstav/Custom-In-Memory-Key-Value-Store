#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <string>
#include <list>
#include <unordered_map> // For O(1) lookup of list iterators
#include <utility> // For std::pair

// Implements an LRU (Least Recently Used) Cache.
class LRUCache {
private:
    // Represents a node in the doubly linked list, storing key-value.
    struct CacheNode {
        // Key of the cached item.
        std::string key;
        // Value of the cached item.
        std::string value;
    };

    // Maximum number of items the cache can hold.
    size_t capacity;
    // Doubly linked list to store cache items by recency. Most recent at front.
    std::list<CacheNode> dll;
    // Unordered map to store key to list iterator for O(1) access to list nodes.
    std::unordered_map<std::string, std::list<CacheNode>::iterator> map;

public:
    // Constructor: initializes the LRU cache with a given capacity.
    explicit LRUCache(size_t cap);

    // Retrieves the value associated with a key. Updates its recency.
    std::string get(const std::string& key);
    // Inserts or updates a key-value pair. Updates its recency.
    // If capacity is exceeded, evicts the least recently used item.
    void put(const std::string& key, const std::string& value);
    // Checks if a key exists in the cache.
    bool contains(const std::string& key);
    // Removes a key from the cache.
    bool remove(const std::string& key);
    // Returns the current size of the cache.
    size_t size() const;
};

#endif // LRU_CACHE_HPP