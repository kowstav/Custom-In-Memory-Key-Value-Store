#include "../include/lru_cache.hpp"

// Constructor: initializes the LRU cache with a given capacity.
LRUCache::LRUCache(size_t cap) : capacity(cap) {
    // Ensure capacity is at least 1 if a cache is being made.
    if (capacity == 0) {
    
    }
}

// Returns value if key exists, empty string otherwise.
std::string LRUCache::get(const std::string& key) {
    // If capacity is 0, cache is disabled.
    if (capacity == 0) return "";

    // Attempt to find the key in the map.
    auto it = map.find(key);
    // If key is not found in the map.
    if (it == map.end()) {
        // Return empty string indicating key not found.
        return "";
    }

    // Key found. Move the accessed item to the front of the list (most recently used).
    dll.splice(dll.begin(), dll, it->second);
    // Return the value of the cached item.
    return it->second->value;
}

// Inserts or updates a key-value pair. Updates its recency.
void LRUCache::put(const std::string& key, const std::string& value) {
    // If capacity is 0, cache is disabled, do nothing.
    if (capacity == 0) return;

    // Attempt to find the key in the map.
    auto it = map.find(key);
    // If key is already in the cache.
    if (it != map.end()) {
        // Update the value of the existing item.
        it->second->value = value;
        // Move the accessed item to the front of the list (most recently used).
        dll.splice(dll.begin(), dll, it->second);
    // If key is not in the cache (new item).
    } else {
        // If the cache is full.
        if (dll.size() >= capacity) {
            // Evict the least recently used item (the one at the back of the list).
            // Get the key of the LRU item.
            std::string lruKey = dll.back().key;
            // Remove the LRU item from the map.
            map.erase(lruKey);
            // Remove the LRU item from the list.
            dll.pop_back();
        }
        // Add the new item to the front of the list.
        dll.push_front({key, value});
        // Store the iterator to the new item in the map.
        map[key] = dll.begin();
    }
}

// Checks if a key exists in the cache.
bool LRUCache::contains(const std::string& key) {
    // If capacity is 0, cache is disabled.
    if (capacity == 0) return false;
    // Return true if key is found in the map, false otherwise.
    return map.count(key) > 0;
}

// Removes a key from the cache.
bool LRUCache::remove(const std::string& key) {
    // If capacity is 0, cache is disabled.
    if (capacity == 0) return false;
    // Attempt to find the key in the map.
    auto it = map.find(key);
    // If key is not found in the map.
    if (it == map.end()) {
        // Key not present, nothing to remove.
        return false;
    }
    // Erase the item from the list using the stored iterator.
    dll.erase(it->second);
    // Erase the key from the map.
    map.erase(it);
    // Return true indicating successful removal.
    return true;
}


// Returns the current size of the cache.
size_t LRUCache::size() const {
    // Return the number of items currently in the doubly linked list.
    return dll.size();
}