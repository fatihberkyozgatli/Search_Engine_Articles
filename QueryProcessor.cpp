#include "QueryProcessor.h"
#include <iostream>

QueryProcessor::QueryProcessor(IndexHandler& indexHandler) : indexHandler(indexHandler) {}

std::vector<int> QueryProcessor::processQuery(const std::string& query) {
    SearchTerms searchTerms = parseQuery(query);
    std::vector<int> results;

    // Entity-based searches are processed first
    for (const auto& entityPair : searchTerms.getEntities()) {
        const std::string& entityType = entityPair.first;
        const std::vector<std::string>& names = entityPair.second;
        
        for (const std::string& name : names) {
            auto entityResults = indexHandler.queryEntities(entityType, name);
            results.insert(results.end(), entityResults.begin(), entityResults.end());
        }
    }

    // Process regular keyword searches
    for (const auto& keyword : searchTerms.getKeywords()) {
        auto keywordResults = indexHandler.query(keyword);
        results.insert(results.end(), keywordResults.begin(), keywordResults.end());
    }

    return results;
}




SearchTerms QueryProcessor::parseQuery(const std::string& query) {
    SearchTerms searchTerms;
    std::istringstream iss(query);
    std::string token;

    while (iss >> token) {
        if (token.rfind("ORG:", 0) == 0) {
            // Entity query for an organization
            searchTerms.addEntity("organization", token.substr(4));
        } else if (token.rfind("PERSON:", 0) == 0) {
            // Entity query for a person
            searchTerms.addEntity("person", token.substr(7));
        } else {
            // Regular keyword
            searchTerms.addKeyword(token);
        }
    }

    return searchTerms;
}
