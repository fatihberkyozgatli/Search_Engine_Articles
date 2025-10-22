#ifndef DOCUMENT_PARSER_H
#define DOCUMENT_PARSER_H

#include "Document.h"
#include "ParsedDocument.h"
#include "Stemmer.h" 
#include "stopwordRemover.h" 
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "./json-develop/single_include/nlohmann/json.hpp"
#include "AVLTree.h"

class DocumentParser {
public:
    DocumentParser(AVLTree& index);

    ParsedDocument parseDocument(const Document& document);

private:
    Stemmer stemmer;
    StopwordRemover stopwordRemover;
    AVLTree& avlTree;

    std::vector<std::string> tokenizeJsonContent(const std::string& jsonContent);

    //method to extract entities from content
    std::unordered_map<std::string, std::set<std::string>> extractEntities(const std::string& content);
};

#endif // DOCUMENT_PARSER_H
