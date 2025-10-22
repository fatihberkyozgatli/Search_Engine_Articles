#include "ParsedDocument.h"

// Constructor
ParsedDocument::ParsedDocument(int docId, 
                               const std::vector<std::string>& processedTokens,
                               const std::unordered_map<std::string, int>& tokenFrequencies,
                               const std::unordered_map<std::string, std::set<std::string>>& entities)
    : documentId(docId), tokens(processedTokens), frequencies(tokenFrequencies), entities(entities) {}

// Getter for the document ID
int ParsedDocument::getDocumentId() const {
    return documentId;
}

// Getter for the processed tokens
const std::vector<std::string>& ParsedDocument::getProcessedTokens() const {
    return tokens;
}

// Getter for the token frequencies
const std::unordered_map<std::string, int>& ParsedDocument::getTokenFrequencies() const {
    return frequencies;
}

// Getter for the entities
const std::unordered_map<std::string, std::set<std::string>>& ParsedDocument::getEntities() const {
    return entities;
}
