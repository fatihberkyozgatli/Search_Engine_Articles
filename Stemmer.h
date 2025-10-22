#ifndef STEMMER_H
#define STEMMER_H

#include <string>
#include "OleanderStemmingLibrary-master/src/english_stem.h" // English stemming header from Oleander

// Class for stemming words
class Stemmer {
public:
    // Method to perform stemming on a given word
    std::string stem(const std::string& word);
};

#endif // STEMMER_H
