#include "../include/trie.hpp"

// Destructor for TrieNode to free children.
TrieNode::~TrieNode() {
    // Iterate through all children in the map.
    for (auto& pair : children) {
        // Delete the child TrieNode.
        delete pair.second;
    }
    // Clear the children map.
    children.clear();
}


// Constructor: initializes the Trie with a root node.
Trie::Trie() {
    // Create a new TrieNode for the root.
    root = new TrieNode();
}

// Destructor: cleans up all nodes in the Trie by deleting the root.
Trie::~Trie() {
    // Delete the root node, which recursively deletes all children.
    delete root;
}

// Inserts a key into the Trie.
void Trie::insert(const std::string& key) {
    // Start traversal from the root node.
    TrieNode* current = root;
    // Iterate through each character of the key.
    for (char ch : key) {
        // If the character is not a child of the current node.
        if (current->children.find(ch) == current->children.end()) {
            // Create a new TrieNode for this character.
            current->children[ch] = new TrieNode();
        }
        // Move to the child node corresponding to the character.
        current = current->children[ch];
    }
    // Mark the last node as the end of the inserted key.
    current->isEndOfKey = true;
}

// Searches for keys in the Trie that start with the given prefix.
std::vector<std::string> Trie::searchPrefix(const std::string& prefix) const {
    // Vector to store the keys found with the given prefix.
    std::vector<std::string> result;
    // Start traversal from the root node.
    TrieNode* current = root;
    // Traverse the Trie according to the characters in the prefix.
    for (char ch : prefix) {
        // If the character is not a child of the current node.
        if (current->children.find(ch) == current->children.end()) {
            // Prefix does not exist, return empty result.
            return result;
        }
        // Move to the child node.
        current = current->children[ch];
    }
    // Prefix found, collect all keys starting from this node.
    collectKeys(current, prefix, result);
    // Return the vector of keys.
    return result;
}

// Recursive helper for collecting keys with a given prefix.
void Trie::collectKeys(TrieNode* node, const std::string& currentPrefix, std::vector<std::string>& result) const {
    // If the current node marks the end of a key.
    if (node->isEndOfKey) {
        // Add the current prefix (which is a complete key) to the result.
        result.push_back(currentPrefix);
    }
    // Iterate through all children of the current node.
    for (auto const& [keyChar, childNode] : node->children) {
        // Recursively call collectKeys for each child, appending the character to the prefix.
        collectKeys(childNode, currentPrefix + keyChar, result);
    }
}

// Checks if a key exists in the Trie.
bool Trie::contains(const std::string& key) const {
    // Start traversal from the root node.
    TrieNode* current = root;
    // Iterate through each character of the key.
    for (char ch : key) {
        // If the character is not a child of the current node.
        if (current->children.find(ch) == current->children.end()) {
            // Key does not exist.
            return false;
        }
        // Move to the child node.
        current = current->children[ch];
    }
    // Return true if the traversal reached the end and it's marked as a key.
    return current != nullptr && current->isEndOfKey;
}


// Recursive helper for deleting a key (and pruning nodes).
bool Trie::deleteKeyRecursive(TrieNode* node, const std::string& key, size_t depth) {
    // If current node is null, key part not found.
    if (!node) {
        // Path for key does not exist.
        return false;
    }

    // If we are at the end of the key.
    if (depth == key.length()) {
        // If this node is marked as end of key.
        if (node->isEndOfKey) {
            // Unmark it as end of key.
            node->isEndOfKey = false;
            // Return true if this node has no children (can be deleted).
            return node->children.empty();
        }
        // Key not found as a complete word here.
        return false;
    }

    // Get the character for the current depth.
    char ch = key[depth];
    // If the character is not a child of the current node.
    if (node->children.find(ch) == node->children.end()) {
        // Key path does not exist further.
        return false;
    }

    // Recursively call delete for the child corresponding to char ch.
    bool shouldDeleteChild = deleteKeyRecursive(node->children[ch], key, depth + 1);

    // If the child node should be deleted (it became empty and was part of the key).
    if (shouldDeleteChild) {
        // Delete the child node from memory.
        delete node->children[ch];
        // Remove the child from the current node's children map.
        node->children.erase(ch);
        // Return true if current node can also be deleted (no other children and not end of another key).
        return !node->isEndOfKey && node->children.empty();
    }
    // Child should not be deleted, so this node should also not be deleted.
    return false;
}

// Deletes a key from the Trie. Returns true if key was found and deleted.
bool Trie::remove(const std::string& key) {
    // If the key is empty, nothing to remove.
    if (key.empty()) return false;
    // Start recursive deletion from the root.
    if (!contains(key)) return false;
    // Call the recursive helper starting from root at depth 0.
    deleteKeyRecursive(root, key, 0);
    // Return true, assuming if contains was true, it's processed.
    return true; 