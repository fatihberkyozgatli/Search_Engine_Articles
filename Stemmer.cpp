#include "Stemmer.h"

// Implementation of the stem method using Oleander Stemming Library
std::string Stemmer::stem(const std::string& word) {
    std::wstring wideWord = std::wstring(word.begin(), word.end()); // Convert to wide string
    stemming::english_stem<> StemEnglish;
    StemEnglish(wideWord);
    return std::string(wideWord.begin(), wideWord.end()); // Convert back to narrow string
}
