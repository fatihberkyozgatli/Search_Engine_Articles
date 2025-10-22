#include "MetaData.h"
#include <regex>

// Constructor for initializing metadata properties
MetaData::MetaData(const std::string& author, const std::string& timestamp, int length)
    : author(author), timestamp(timestamp), length(length) {}

// Getters...

// ...author
const std::string& MetaData::getAuthor() const {
    return author;
}

// ...timestamp
const std::string& MetaData::getTimestamp() const {
    return timestamp;
}

// ...length
int MetaData::getLength() const {
    return length;
}

// Setters...

// ...author
void MetaData::setAuthor(const std::string& newAuthor) {
    author = newAuthor;
}

// ...timestamp
void MetaData::setTimestamp(const std::string& newTimestamp) {
    // Regular expression to validate timestamp format
    std::regex timestampFormat(R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3}\+\d{2}:\d{2}$)");
    if (std::regex_match(newTimestamp, timestampFormat)) {
        timestamp = newTimestamp;
    } else {
        throw std::invalid_argument("Invalid timestamp format");
    }
}

// ...length
void MetaData::setLength(int newLength) {
    if (newLength >= 0) {
        length = newLength;
    } else {
        throw std::invalid_argument("Length cannot be negative");
    }
}
