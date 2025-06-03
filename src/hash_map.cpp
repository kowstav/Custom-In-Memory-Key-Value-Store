#include "../include/hash_map.hpp"
#include <stdexcept> 
// Constructor: initializes the hash map with a given capacity.
HashMap::HashMap(size_t capacity) : currentSize(0), tableCapacity(capacity) {
    // Resize the table to the specified capacity.
    table.resize(tableCapacity);
}

// Hash function to map a key to an index in the table.
size_t HashMap::hash(const std::string& key) const {
    // Initialize hash value.
    size_t hashCode = 0;
    // Iterate through each character of the key.
    for (char c : key) {
        // A simple hash function: sum of char values multiplied by a prime.
        hashCode = (hashCode * 31 + c) % tableCapacity;
    }
    // Return the computed hash code modulo table capacity.
    return hashCode;
}

// Inserts or updates a key-value pair.
void HashMap::set(const std::string& key, const std::string& value) {
    // Get the hash index for the key.
    size_t index = hash(key);
    // Iterate through the bucket (chain) at the computed index.
    for (auto& node : table[index]) {
        // If key is found, update its value.
        if (node.first == key) {
            // Update the value of the existing key.
            node.second = value;
            // Return after updating.
            return;
        }
    }
    // If key is not found, add a new key-value pair to the bucket.
    table[index].emplace_back(key, value);
    // Increment the current size of the hash map.
    currentSize++;
}

// Retrieves the value associated with a key. Returns empty string if not found.
std::string HashMap::get(const std::string& key) {
    // Get the hash index for the key.
    size_t index = hash(key);
    // Iterate through the bucket at the computed index.
    for (const auto& node : table[index]) {
        // If key is found, return its value.
        if (node.first == key) {
            // Return the value associated with the key.
            return node.second;
        }
    }
    // Return an empty string if the key is not found.
    return ""; // Or throw an exception, e.g., std::out_of_range("Key not found")
}

// Deletes a key-value pair. Returns true if key was found and deleted, false otherwise.
bool HashMap::remove(const std::string& key) {
    // Get the hash index for the key.
    size_t index = hash(key);
    // Get a reference to the bucket.
    auto& bucket = table[index];
    // Iterate through the bucket.
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        // If the key is found.
        if (it->first == key) {
            // Erase the key-value pair from the list (bucket).
            bucket.erase(it);
            // Decrement the current size of the hash map.
            currentSize--;
            // Return true indicating successful removal.
            return true;
        }
    }
    // Return false if the key was not found.
    return false;
}

// Checks if a key exists in the hash map.
bool HashMap::contains(const std::string& key) {
    // Get the hash index for the key.
    size_t index = hash(key);
    // Iterate through the bucket at the computed index.
    for (const auto& node : table[index]) {
        // If key is found, return true.
        if (node.first == key) {
            // Key exists in the hash map.
            return true;
        }
    }
    // Key does not exist in the hash map.
    return false;
}

// Returns the current number of elements in the hash map.
size_t HashMap::size() const {
    // Return the number of key-value pairs stored.
    return currentSize;
}

// Rehashes the table when load factor exceeds a threshold (stub).
void HashMap::rehash() {}