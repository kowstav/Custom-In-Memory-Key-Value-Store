#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <string>
#include <vector>
#include <list> // For chaining
#include <utility> // For std::pair

// Defines a simple Hash Map with string keys and string values using chaining for collision resolution.
class HashMap {
private:
    // Represents a key-value pair in a hash map bucket.
    using BucketNode = std::pair<std::string, std::string>;
    // Each bucket is a list of key-value pairs (nodes) for chaining.
    using Bucket = std::list<BucketNode>;
    // The hash table is a vector of buckets.
    std::vector<Bucket> table;
    // Current number of elements in the hash map.
    size_t currentSize;
    // Capacity of the hash table (number of buckets).
    size_t tableCapacity;

    // Hash function to map a key to an index in the table.
    size_t hash(const std::string& key) const;
    // Rehashes the table when load factor exceeds a threshold (not fully implemented here for brevity).
    void rehash(); // Declaration for future expansion

public:
    // Constructor: initializes the hash map with a given capacity.
    explicit HashMap(size_t capacity = 101); // Default capacity, prime number

    // Inserts or updates a key-value pair.
    void set(const std::string& key, const std::string& value);
    // Retrieves the value associated with a key. Returns empty string if not found.
    std::string get(const std::string& key);
    // Deletes a key-value pair. Returns true if key was found and deleted, false otherwise.
    bool remove(const std::string& key);
    // Checks if a key exists in the hash map.
    bool contains(const std::string& key);
    // Returns the current number of elements in the hash map.
    size_t size() const;
};

#endif // HASH_MAP_HPP