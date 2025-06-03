# Custom In-Memory Key-Value Store with Advanced Indexing

This project implements a custom in-memory key-value store in C++. It features core key-value operations (SET, GET, DELETE) backed by a custom hash map, prefix-based key searching using a Trie, an LRU (Least Recently Used) cache for optimizing frequent accesses, and a Bloom filter for fast rejection of queries for non-existent keys.

## Features

* **Core Key-Value Operations:**
    * `SET key value`: Inserts or updates a key-value pair.
    * `GET key`: Retrieves the value for a key.
    * `DELETE key`: Removes a key-value pair.
* **Advanced Indexing & Search:**
    * **Prefix Search:** `PREFIX search_prefix` lists all keys starting with `search_prefix`, implemented using a Trie.
* **Performance Optimizations:**
    * **LRU Cache:** Maintains a cache of most-recently-used entries to speed up `GET` operations. Implemented with a doubly linked list and a hash map for O(1) access and eviction.
    * **Bloom Filter:** A probabilistic data structure (`BLOOM CHECK key`) to quickly determine if a key *might* exist, reducing lookups for keys that are definitely not in the store.
* **Custom Data Structures:**
    * **Hash Map:** Implemented with chaining for collision resolution.
    * **Trie:** For efficient prefix-based key searches.
    * **Doubly Linked List & Map:** Components of the LRU Cache.
    * **Bit Array & Multiple Hash Functions:** Components of the Bloom Filter.
* **Command-Line Interface (CLI):**
    * A REPL (Read-Eval-Print Loop) allows interactive use of the key-value store.
* **Build System:** CMake for building the project and its tests.
* **Unit Tests:** Basic tests for individual data structure components and the main KVStore.

## Tech Stack

* **Language:** C++17
* **Build System:** CMake
* **Testing:** Basic assertion-based tests (runnable via CTest if `BUILD_TESTS` is ON).

## Project Folder Structure
```
key_value_store/
├── src/                      # Source files (.cpp)
│   ├── main.cpp              # CLI main entry point
│   ├── kv_store.cpp          # High-level interface for store
│   ├── hash_map.cpp          # Custom hash map logic
│   ├── trie.cpp              # Prefix tree
│   ├── lru_cache.cpp         # LRU cache logic
│   ├── bloom_filter.cpp      # Bloom filter implementation
│   └── utils.cpp             # Common helpers (e.g., hash functions)
│
├── include/                  # Header files (.hpp)
│   ├── kv_store.hpp
│   ├── hash_map.hpp
│   ├── trie.hpp
│   ├── lru_cache.hpp
│   ├── bloom_filter.hpp
│   └── utils.hpp
│
├── tests/                    # Unit test source files
│   ├── test_kv_store.cpp
│   ├── test_hash_map.cpp
│   ├── test_trie.cpp
│   ├── test_lru_cache.cpp
│   ├── test_bloom_filter.cpp
│
├── docs/                     # Documentation (this file)
│   └── README.md
│
├── data/                     # Sample data or command files
│   └── sample_commands.txt
│
├── CMakeLists.txt            # CMake build configuration
└── run.sh                    # Build and run script
```

## Time Complexity Summary

The expected average time complexities for the main operations are:
```

| Operation     | Time Complexity                                     | Notes                                                                    |
| :------------ | :-------------------------------------------------- | :----------------------------------------------------------------------- |
| SET key value | O(1) avg for HashMap + O(L) for Trie + O(1) for LRU + O(H) for Bloom | L = key length, H = num hash functions for Bloom Filter. Overall dominated by Trie or effectively O(1) avg. |
| GET key       | O(H) for Bloom + O(1) for LRU/HashMap avg           | If key in cache O(1). If not, O(1) avg from HashMap + O(1) for LRU update. Overall O(1) avg. |
| DELETE key    | O(1) avg for HashMap + O(L) for Trie + O(1) for LRU | Overall dominated by Trie or effectively O(1) avg. Bloom filter does not truly delete. |
| PREFIX query  | O(P + M*L<sub>avg</sub>)                                | P = prefix length, M = number of matched keys, L<sub>avg</sub> = average length of matched keys. Traverses Trie. |
| LRU update    | O(1)                                                | For `get` or `put` operations that hit/update the cache.                   |
| Bloom check   | O(H)                                                | H = number of hash functions for Bloom Filter.                             |

```
*Where:*
* `L`: length of the key.
* `P`: length of the prefix.
* `M`: number of keys matching the prefix.
* `L_avg`: average length of keys matching the prefix.
* `H`: number of hash functions used by the Bloom Filter.
* *Average case for HashMap operations assumes a good hash function and manageable load factor.*

## Setup and Build

1.  **Prerequisites:**
    * C++17 compatible compiler (GCC, Clang, etc.)
    * CMake (version 3.14+)

2.  **Clone the repository (if applicable) and navigate to the root directory.**

3.  **Build the project:**
    ```bash
    mkdir build
    cd build
    cmake ..       # To build with tests (default)
    # cmake -DBUILD_TESTS=OFF ..  # To build without tests
    make
    ```


### CLI Application

After building, the main CLI executable will be in the `build/` directory (or `build/src/` depending on CMake setup, check specific CMake settings, usually just `build/kv_store_cli`).
