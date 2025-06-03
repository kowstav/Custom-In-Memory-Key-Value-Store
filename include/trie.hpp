#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <vector>
#include <map> // For children nodes

// Represents a node in the Trie.
struct TrieNode {
    // Map of characters to child TrieNode pointers.
    std::map<char, TrieNode*> children;
    // Flag to mark if a key ends at this node.
    bool isEndOfKey;

    // Constructor for TrieNode.
    TrieNode() : isEndOfKey(false) {}
    // Destructor to free children (needed for proper memory management).
    ~TrieNode();
};

// Implements a Trie data structure for prefix-based key search.
class Trie {
private:
    // The root node of the Trie.
    TrieNode* root;

    // Recursive helper for collecting keys with a given prefix.
    void collectKeys(TrieNode* node, const std::string& currentPrefix, std::vector<std::string>& result) const;
    // Recursive helper for deleting a key (and pruning nodes).
    bool deleteKeyRecursive(TrieNode* node, const std::string& key, size_t depth);


public:
    // Constructor: initializes the Trie with a root node.
    Trie();
    // Destructor: cleans up all nodes in the Trie.
    ~Trie();

    // Inserts a key into the Trie.
    void insert(const std::string& key);
    // Searches for keys in the Trie that start with the given prefix.
    std::vector<std::string> searchPrefix(const std::string& prefix) const;
    // Deletes a key from the Trie. Returns true if key was found and deleted.
    bool remove(const std::string& key);
    // Checks if a key exists in the Trie.
    bool contains(const std::string& key) const;
};

#endif // TRIE_HPP