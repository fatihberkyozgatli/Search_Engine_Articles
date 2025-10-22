#ifndef PARSED_DOCUMENT_H
#define PARSED_DOCUMENT_H

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

// Represents a processed document
class ParsedDocument {
public:
    // Constructor initializing the document with its ID, token frequencies, and entities
    ParsedDocument(int docId, 
                   const std::vector<std::string>& processedTokens,
                   const std::unordered_map<std::string, int>& tokenFrequencies,
                   const std::unordered_map<std::string, std::set<std::string>>& entities);

    // Getter for the document ID
    int getDocumentId() const;

    // Getter for the processed tokens
    const std::vector<std::string>& getProcessedTokens() const;

    // Getter for the token frequencies
    const std::unordered_map<std::string, int>& getTokenFrequencies() const;

    // Getter for the entities
    const std::unordered_map<std::string, std::set<std::string>>& getEntities() const;

private:
    int documentId; // Unique identifier for the document
    std::vector<std::string> tokens; // Processed tokens
    std::unordered_map<std::string, int> frequencies; // Token frequencies
    std::unordered_map<std::string, std::set<std::string>> entities; // Entities categorized by type
};

#endif // PARSED_DOCUMENT_H
