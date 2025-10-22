#include "SearchTerms.h"

void SearchTerms::addKeyword(const std::string& keyword) {
    keywords.push_back(keyword);
}

void SearchTerms::addEntity(const std::string& type, const std::string& name) {
    entities[type].push_back(name);
}

const std::vector<std::string>& SearchTerms::getKeywords() const {
    return keywords;
}

const std::unordered_map<std::string, std::vector<std::string>>& SearchTerms::getEntities() const {
    return entities;
}

bool SearchTerms::hasEntities() const {
    return !entities.empty();
}
