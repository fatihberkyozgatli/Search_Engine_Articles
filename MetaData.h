#ifndef METADATA_H
#define METADATA_H

#include <string>

// Class representing the metadata of a document.
class MetaData {
public:
    MetaData(const std::string& author, const std::string& timestamp, int length);

    // Getters for metadata fields
    const std::string& getAuthor() const;
    const std::string& getTimestamp() const;
    int getLength() const;

    // Setters for metadata fields
    void setAuthor(const std::string& author);
    void setTimestamp(const std::string& timestamp);
    void setLength(int length);

private:
    std::string author;    // Author of the document
    std::string timestamp; // Publication timestamp of the document
    int length;            // Length of the document in characters/words
};

#endif // METADATA_H
