#ifndef SEARCH_TERMS_H
#define SEARCH_TERMS_H

#include <string>
#include <vector>
#include <unordered_map>

class SearchTerms {
public:
    // Add a keyword to the search terms
    void addKeyword(const std::string& keyword);

    // Add an entity to the search terms
    void addEntity(const std::string& type, const std::string& name);

    // Get all keywords
    const std::vector<std::string>& getKeywords() const;

    // Get all entities
    const std::unordered_map<std::string, std::vector<std::string>>& getEntities() const;

    // Check if there are any entities
    bool hasEntities() const;

private:
    std::vector<std::string> keywords;
    std::unordered_map<std::string, std::vector<std::string>> entities; // Entity type to names
};

#endif // SEARCH_TERMS_H
