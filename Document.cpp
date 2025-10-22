#include "Document.h"

// Constructor for initializing Document properties
Document::Document(int id, const std::string& title, const std::string& content, const MetaData& metadata)
    : docId(id), title(title), content(content), metadata(metadata) {}

// Copy constructor
Document::Document(const Document& other)
    : docId(other.docId), title(other.title), content(other.content), metadata(other.metadata) {}

// Move constructor
Document::Document(Document&& other) noexcept
    : docId(other.docId), title(std::move(other.title)), content(std::move(other.content)), metadata(std::move(other.metadata)) {}

// Copy assignment operator
Document& Document::operator=(const Document& other) {
    if (this != &other) {
        docId = other.docId;
        title = other.title;
        content = other.content;
        metadata = other.metadata;
    }
    return *this;
}

// Move assignment operator
Document& Document::operator=(Document&& other) noexcept {
    if (this != &other) {
        docId = other.docId;
        title = std::move(other.title);
        content = std::move(other.content);
        metadata = std::move(other.metadata);
    }
    return *this;
}
// Returns Id
int Document::getId() const {
    return docId;
}

// Returns Title 
const std::string& Document::getTitle() const {
    return title;
}

//Returns Content
const std::string& Document::getContent() const {
    return content;
}
