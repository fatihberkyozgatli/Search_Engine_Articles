#include "stopwordRemover.h"
#include <fstream>
#include <sstream>

// Constructor
StopwordRemover::StopwordRemover() {
}

// Load stopwords from a file
void StopwordRemover::loadStopwords(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string stopword;
        while (iss >> stopword) {
            stopwords.insert(stopword);
        }
    }
}

// Check if a word is a stopword
bool StopwordRemover::isStopword(const std::string& word) const {
    return stopwords.find(word) != stopwords.end();
}