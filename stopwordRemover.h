#ifndef STOPWORD_REMOVER_H
#define STOPWORD_REMOVER_H

#include <string>
#include <unordered_set>

// Class for removing stopwords from text
class StopwordRemover {
public:
    // Constructor
    StopwordRemover();

    // Load stopwords from a file
    void loadStopwords(const std::string& filename);

    // Check if a word is a stopword
    bool isStopword(const std::string& word) const;

private:
    std::unordered_set<std::string> stopwords; // Set of stopwords
};

#endif // STOPWORD_REMOVER_H
