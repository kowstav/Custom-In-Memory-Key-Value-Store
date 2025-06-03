#include "../include/kv_store.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // For parsing input line

// Helper function to split a string by a delimiter.
std::vector<std::string> splitString(const std::string& s, char delimiter) {
    // Vector to store parts of the string.
    std::vector<std::string> tokens;
    // Current token being built.
    std::string token;
    // String stream to process the input string.
    std::istringstream tokenStream(s);
    // Read parts of the string separated by the delimiter.
    while (std::getline(tokenStream, token, delimiter)) {
        // Add the extracted token to the vector.
        tokens.push_back(token);
    }
    // Return the vector of tokens.
    return tokens;
}

// Main function for the CLI interface.
int main() {
    // Create an instance of the Key-Value Store.
    KVStore store;
    // String to hold user input.
    std::string line;

    // Print welcome message for the REPL.
    std::cout << "Custom In-Memory Key-Value Store CLI" << std::endl;
    // Print usage instructions.
    std::cout << "Commands: SET <key> <value>, GET <key>, DEL <key>, PREFIX <prefix>, BLOOM <key>, EXIT" << std::endl;

    // REPL (Read-Eval-Print Loop).
    while (true) {
        // Print command prompt.
        std::cout << "> ";
        // Read a line of input from the user.
        if (!std::getline(std::cin, line)) {
            // Break loop on EOF (e.g., Ctrl+D).
            break;
        }

        // Split the input line into command and arguments.
        std::vector<std::string> args = splitString(line, ' ');
        // If no arguments entered, continue to next iteration.
        if (args.empty()) {
            // Skip empty input.
            continue;
        }

        // Get the command from the first argument.
        std::string command = args[0];

        // Process SET command.
        if (command == "SET" && args.size() == 3) {
            // Set key-value pair in the store.
            store.set(args[1], args[2]);
            // Print confirmation message.
            std::cout << "OK" << std::endl;
        // Process GET command.
        } else if (command == "GET" && args.size() == 2) {
            // Get value for the key from the store.
            std::string value = store.get(args[1]);
            // If value is not empty (key found).
            if (!value.empty() || store.mightContain(args[1])) { // Check mightContain for keys that map to empty strings
                // Print the retrieved value.
                std::cout << "\"" << value << "\"" << std::endl;
            } else {
                // Print message if key not found.
                std::cout << "(nil)" << std::endl; // Or (key not found)
            }
        // Process DEL command.
        } else if (command == "DEL" && args.size() == 2) {
            // Remove key from the store.
            if (store.remove(args[1])) {
                // Print confirmation if key was deleted.
                std::cout << "OK (deleted)" << std::endl;
            } else {
                // Print message if key was not found to delete.
                std::cout << "OK (key not found)" << std::endl;
            }
        // Process PREFIX command.
        } else if (command == "PREFIX" && args.size() == 2) {
            // Search for keys with the given prefix.
            std::vector<std::string> keys = store.prefixSearch(args[1]);
            // If keys are found.
            if (!keys.empty()) {
                // Iterate through found keys.
                for (size_t i = 0; i < keys.size(); ++i) {
                    // Print each key.
                    std::cout << (i + 1) << ") " << keys[i] << std::endl;
                }
            } else {
                // Print message if no keys match the prefix.
                std::cout << "(no keys found with this prefix)" << std::endl;
            }
        // Process BLOOM command (check Bloom Filter).
        } else if (command == "BLOOM" && args.size() == 2) {
            // Check if the key might be in the store using Bloom Filter.
            if (store.mightContain(args[1])) {
                // Print message if key might be present.
                std::cout << "Key \"" << args[1] << "\" MIGHT be present (check GET for confirmation)." << std::endl;
            } else {
                // Print message if key is definitely not present.
                std::cout << "Key \"" << args[1] << "\" is DEFINITELY NOT present." << std::endl;
            }
        // Process EXIT command.
        } else if (command == "EXIT") {
            // Print goodbye message and break loop.
            std::cout << "Exiting store." << std::endl;
            // Terminate the loop.
            break;
        // Handle unknown commands.
        } else {
            // Print error message for invalid command.
            std::cout << "ERR: Unknown command or incorrect arguments. Available: SET, GET, DEL, PREFIX, BLOOM, EXIT" << std::endl;
        }
    }
    // Return 0 indicating successful execution.
    return 0;
}