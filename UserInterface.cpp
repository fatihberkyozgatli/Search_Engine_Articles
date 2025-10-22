#include "UserInterface.h"
#include "IndexHandler.h"
#include <iostream>
#include <string>
#include <chrono>

UserInterface::UserInterface(QueryProcessor& queryProcessor, IndexHandler& indexHandler)
    : queryProcessor(queryProcessor), indexHandler(indexHandler) {}

void UserInterface::start() {
    bool running = true;
    while (running) {
        mainMenu();
        std::string choice = getInput("Enter your choice: ");
        if (choice == "index") {
            handleIndexingCommand();
        } else if (choice == "query") {
            handleQueryCommand();
        } else if (choice == "exit") {
            running = false;
        } else {
            std::cout << "Invalid command. Please try again.\n";
        }
    }
}

void UserInterface::mainMenu() {
    std::cout << "Commands:\n";
    std::cout << "  index - Index a directory\n";
    std::cout << "  query - Perform a search query\n";
    std::cout << "  exit  - Exit the program\n";
}

void UserInterface::handleIndexingCommand() {
    std::string directory = getInput("Enter directory path: ");

    // Start the timer
    auto startTime = std::chrono::high_resolution_clock::now();

    // Instantiate or reference a DocumentParser and IndexHandler
    DocumentParser parser(indexHandler.getAvlTree());

    // Index the specified directory
    try {
        std::cout << "Indexing documents from directory: " << directory << std::endl;

        // Loop through each file in the directory and index it
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (std::filesystem::is_regular_file(entry)) {
                std::string filePath = entry.path().string();

                // Read and parse the document
                indexHandler.readAndParseDocument(filePath, parser);
            }
        }

        std::cout << "Indexing completed successfully." << std::endl;

        // Stop the timer
        auto endTime = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

        // Display the duration
        std::cout << "Indexing completed in " << duration << " seconds." << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::string saveChoice = getInput("Save index to file? (yes/no): ");
    if (saveChoice == "yes") {
        std::string filepath = getInput("Enter file path to save index: ");
        try {
            indexHandler.saveIndexToFile(filepath);
            std::cout << "Index saved successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error saving index: " << e.what() << std::endl;
        }
    }
}


void UserInterface::handleQueryCommand() {
    std::string query = getInput("Enter search query: ");
    
    // Call QueryProcessor to process the query
    std::vector<int> resultDocIDs = queryProcessor.processQuery(query);

    // Display results
    if (resultDocIDs.empty()) {
        std::cout << "No results found." << std::endl;
    }
    else {
        std::cout << "Top 10 documents with IDs (or less if fewer results): ";
        int count = 0;
        for (const int docID : resultDocIDs) {
            if (count >= 10) break; // Limit to top 10 results
            std::cout << docID << " ";
            count++;
        }
        std::cout << std::endl;
    }
}

std::string UserInterface::getInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}
