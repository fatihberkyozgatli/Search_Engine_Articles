#include "DocumentParser.h"
#include <sstream>
#include "./json-develop/single_include/nlohmann/json.hpp"
#include <cctype> // for std::ispunct

using json = nlohmann::json;

DocumentParser::DocumentParser(AVLTree& index) : avlTree(index) {
    stopwordRemover.loadStopwords("./stopwords.txt");
}

ParsedDocument DocumentParser::parseDocument(const Document& document) {
    std::vector<std::string> tokens = tokenizeJsonContent(document.getContent());
    auto entities = extractEntities(document.getContent());

    std::unordered_map<std::string, int> tokenFrequencies;
    for (std::string& token : tokens) {
        if (!stopwordRemover.isStopword(token)) {
            token = stemmer.stem(token);
            tokenFrequencies[token]++;
        }
    }

    for (const auto& [token, frequency] : tokenFrequencies) {
        avlTree.insert(token, document.getId(), frequency);
    }

    return ParsedDocument(document.getId(), tokens, tokenFrequencies, entities);
}


std::vector<std::string> DocumentParser::tokenizeJsonContent(const std::string& jsonContent) {
    std::vector<std::string> tokens;
    json parsedJson = json::parse(jsonContent);
    std::string textContent;

    if (parsedJson.contains("text") && parsedJson["text"].is_string()) {
        textContent = parsedJson["text"];
    }

    std::istringstream iss(textContent);
    std::string token;
    std::string cleanedToken;

    while (iss >> token) {
        cleanedToken.clear();
        for (char c : token) {
            if (!std::ispunct(c)) {
                cleanedToken += c;
            }
        }
        if (!cleanedToken.empty()) {
            tokens.push_back(cleanedToken);
        }
    }

    return tokens;
}

std::unordered_map<std::string, std::set<std::string>> DocumentParser::extractEntities(const std::string& jsonContent) {
    std::unordered_map<std::string, std::set<std::string>> entities;
    json parsedJson = json::parse(jsonContent);

    // Check and extract organizations
    if (parsedJson.contains("entities") && parsedJson["entities"].contains("organizations")) {
        for (const auto& org : parsedJson["entities"]["organizations"]) {
            if (org.contains("name")) {
                entities["organizations"].insert(org["name"]);
            }
        }
    }

    // Check and extract persons
    if (parsedJson.contains("entities") && parsedJson["entities"].contains("persons")) {
        for (const auto& person : parsedJson["entities"]["persons"]) {
            if (person.contains("name")) {
                entities["persons"].insert(person["name"]);
            }
        }
    }
return entities;
}

