#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include "ParsedDocument.h"
#include "DocumentParser.h"
#include "AVLTree.h"
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

class IndexHandler {
public:
    IndexHandler();
    
    // Process a parsed document to update the indices
    void indexDocument(const ParsedDocument& parsedDoc);

    // Additional method for handling organization and person indices
    void indexEntities(const ParsedDocument& parsedDoc, 
                       const std::unordered_map<std::string, std::set<std::string>>& entities);

    // Perform a query search and return a sorted list of document IDs
    std::vector<int> query(const std::string& searchTerm);

    // Method for querying entities
    std::vector<int> queryEntities(const std::string& entityType, const std::string& entityName);

    // Method for indexing a directory
    void indexDirectory(const std::string& directoryPath);

    void readAndParseDocument(const std::string& filePath, DocumentParser& parser);

    std::string readFileContent(const std::string& filePath);

    AVLTree& getAvlTree(); 

    // Methods for file operations
    void saveIndexToFile(const std::string& filepath);
    void loadIndexFromFile(const std::string& filepath);
    
    // Method to serialize orgIndex and personIndex to a string
    std::string serializeOrgAndPersonIndices();

    // Method to deserialize orgIndex and personIndex from a string
    void deserializeOrgAndPersonIndices(const std::string& data);

    // Method to update the term frequency
    void updateCumulativeTermFrequency(const std::string& term, int frequency) {
        cumulativeTermFrequencies[term] += frequency;
    }
    
    // Method to find the most frequent term
    std::string findMostFrequentTerm() const;
    
private:
    AVLTree wordIndex; // Inverted index for words
    std::unordered_map<std::string, std::set<int>> orgIndex; // Index for organizations
    std::unordered_map<std::string, std::set<int>> personIndex; // Index for person entities
    int nextDocId = 0; 
    std::unordered_map<std::string, int> cumulativeTermFrequencies;
};

#endif // INDEX_HANDLER_H
