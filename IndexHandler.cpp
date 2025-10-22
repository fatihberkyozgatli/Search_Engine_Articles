#include "IndexHandler.h"
#include "DocumentParser.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include "./json-develop/single_include/nlohmann/json.hpp"

namespace fs = std::filesystem;

IndexHandler::IndexHandler() {
}

void IndexHandler::indexDocument(const ParsedDocument& parsedDoc) {
    // Iterate over token frequencies and update wordIndex
    for (const auto& [token, frequency] : parsedDoc.getTokenFrequencies()) {
        wordIndex.insert(token, parsedDoc.getDocumentId(), frequency);
    }

    // Index organizations and persons
    indexEntities(parsedDoc, parsedDoc.getEntities());
}

void IndexHandler::indexEntities(const ParsedDocument& parsedDoc, 
                                 const std::unordered_map<std::string, std::set<std::string>>& entities) {
    for (const auto& org : entities.at("organizations")) {
        orgIndex[org].insert(parsedDoc.getDocumentId());
    }
    for (const auto& person : entities.at("persons")) {
        personIndex[person].insert(parsedDoc.getDocumentId());
    }
}

std::vector<int> IndexHandler::queryEntities(const std::string& entityType, const std::string& entityName) {
    std::vector<int> results;
    if (entityType == "organization") {
        auto it = orgIndex.find(entityName);
        if (it != orgIndex.end()) {
            results.assign(it->second.begin(), it->second.end());
        }
    } else if (entityType == "person") {
        auto it = personIndex.find(entityName);
        if (it != personIndex.end()) {
            results.assign(it->second.begin(), it->second.end());
        }
    }
    return results;
}

std::vector<int> IndexHandler::query(const std::string& searchTerm) {
    std::vector<int> result;
    std::map<int, int, std::greater<int>> relevanceScores; // Map of DocumentID to RelevanceScore

    if (searchTerm.rfind("ORG:", 0) == 0) {
        std::string orgName = searchTerm.substr(4);
        result = queryEntities("organization", orgName);
    } else if (searchTerm.rfind("PERSON:", 0) == 0) {
        std::string personName = searchTerm.substr(7);
        result = queryEntities("name", personName);
    } else {
        // Process regular token search
        auto docInfos = wordIndex.search(searchTerm); // Search the AVLTree
        for (const auto& docInfo : docInfos) {
            relevanceScores[docInfo.docID] = docInfo.frequency; // Use frequency as relevance score
        }

        // Sort results based on relevance (highest frequency first)
        std::vector<std::pair<int, int>> sortedResults(relevanceScores.begin(), relevanceScores.end());
        std::sort(sortedResults.begin(), sortedResults.end(), 
                  [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                      return a.second > b.second; // Sort by frequency in descending order
                  });

        // Resize to get only top 10 results
        if (sortedResults.size() > 10) {
        sortedResults.resize(10);
        }

        // Extracting sorted document IDs
        std::vector<int> result;
        for (const auto& pair : sortedResults) {
        result.push_back(pair.first);
    }

    return result;
    }
    return result;
    }


void IndexHandler::indexDirectory(const std::string& directoryPath) {
    DocumentParser parser(wordIndex); // Create a DocumentParser instance

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            std::string filePath = entry.path().string();
            readAndParseDocument(filePath, parser); 
        }
    }
}

void IndexHandler::readAndParseDocument(const std::string& filePath, DocumentParser& parser) {
    std::string fileContent = readFileContent(filePath);
    Document doc(nextDocId++, "title", fileContent, MetaData("author", "timestamp", 0)); // Increment doc ID for each document
    
    parser.parseDocument(doc);
}

// Helper function for ^^
std::string IndexHandler::readFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

AVLTree& IndexHandler::getAvlTree() {
    return wordIndex; 
}

void IndexHandler::saveIndexToFile(const std::string& filepath) {
    std::ofstream outFile(filepath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file for writing: " + filepath);
    }

    // Serialize AVL tree and other indices
    std::string avlTreeData = wordIndex.serialize();
    std::string orgAndPersonData = serializeOrgAndPersonIndices();

    nlohmann::json indexData;
    indexData["avlTree"] = avlTreeData;
    indexData["orgAndPerson"] = orgAndPersonData;

    outFile << indexData.dump();
    outFile.close();
}

void IndexHandler::loadIndexFromFile(const std::string& filepath) {
    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file for reading: " + filepath);
    }

    nlohmann::json indexData;
    inFile >> indexData;
    inFile.close();

    // Deserialize data
    wordIndex.deserialize(indexData["avlTree"]);
    deserializeOrgAndPersonIndices(indexData["orgAndPerson"]);
}

std::string IndexHandler::serializeOrgAndPersonIndices() {
    nlohmann::json jsonData;

    // Serialize orgIndex
    nlohmann::json orgJson;
    for (const auto& [key, value] : orgIndex) {
        orgJson[key] = nlohmann::json::array();
        for (const auto& docId : value) {
            orgJson[key].push_back(docId);
        }
    }
    jsonData["organizations"] = orgJson;

    // Serialize personIndex
    nlohmann::json personJson;
    for (const auto& [key, value] : personIndex) {
        personJson[key] = nlohmann::json::array();
        for (const auto& docId : value) {
            personJson[key].push_back(docId);
        }
    }
    jsonData["persons"] = personJson;

    return jsonData.dump(); // Convert JSON object to string
}



void IndexHandler::deserializeOrgAndPersonIndices(const std::string& data) {
    nlohmann::json jsonData = nlohmann::json::parse(data);

    // Clear existing data
    orgIndex.clear();
    personIndex.clear();

    // Deserialize orgIndex
    if (jsonData.contains("organizations") && jsonData["organizations"].is_object()) {
        for (const auto& [key, value] : jsonData["organizations"].items()) {
            std::set<int> docIds(value.begin(), value.end());
            orgIndex[key] = docIds;
        }
    }

    // Deserialize personIndex
    if (jsonData.contains("persons") && jsonData["persons"].is_object()) {
        for (const auto& [key, value] : jsonData["persons"].items()) {
            std::set<int> docIds(value.begin(), value.end());
            personIndex[key] = docIds;
        }
    }
}

// Function to find the most frequently used term
    std::string IndexHandler::findMostFrequentTerm() const {
    std::string mostFrequentTerm;
    int highestFrequency = 0;

    for (const auto& termFreq : cumulativeTermFrequencies) {
        if (termFreq.second > highestFrequency) {
            highestFrequency = termFreq.second;
            mostFrequentTerm = termFreq.first;
        }
    }

    return mostFrequentTerm;
}
