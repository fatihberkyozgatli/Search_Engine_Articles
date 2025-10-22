#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <unordered_map>
#include "MetaData.h"

// Represents a single document in the search engine.
class Document {
public:
    //Constructor
    Document(int id, const std::string& title, const std::string& content, const MetaData& metadata);
    // Move constructor
    Document(Document&& other) noexcept;
    // Copy constructor
    Document(const Document& other);
    // Copy assignment operator
    Document& operator=(const Document& other);
    // Move assignment operator
    Document& operator=(Document&& other) noexcept;

    // Returns ID
    int getId() const;
    // Returns Title
    const std::string& getTitle() const;
    // Returns Content
    const std::string& getContent() const;
    // Returns MetaData
    const MetaData& getMetaData() const;

private:
    int docId;                  // Unique identifier for the document
    std::string title;          // Title of the document
    std::string content;        // Content of the document
    MetaData metadata;          // the associated Meta Data
};

#endif // DOCUMENT_H
