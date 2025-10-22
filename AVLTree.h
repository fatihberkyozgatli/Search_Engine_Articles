#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <vector>
#include <sstream>

// Structure to hold information about a document: ID and frequency.
struct DocInfo {
    int docID;
    int frequency;
    DocInfo(int id, int freq); // Constructor
};

// Node class
class AVLNode {
public:
    std::string key; // The key value
    std::vector<DocInfo> docList; // List of documents where the key appears
    AVLNode *left; // Pointer to the left child
    AVLNode *right; // Pointer to the right child
    int height; // Height of the node
    AVLNode* find(const std::string& key); // Find a key
    AVLNode(std::string k, int docID, int frequency); // Updated constructor
    void addDocInfo(int docID, int frequency); // Method to add document information
};

// AVL Tree class
class AVLTree {
public:
    AVLTree(); // Constructor
    ~AVLTree(); // Destructor
    void destroyTree(AVLNode* node); // Remove tree
    void insert(std::string key, int docID, int frequency); // Insert a new key
    void remove(std::string key); // Remove a key
    void inorderTraversal(); // Perform inorder traversal
    std::string serialize(); // Serialize the tree
    void deserialize(const std::string& data); // Deserialize the tree
    void updateDocInfo(std::string key, int docID, int newFrequency); // Update document information
    AVLNode *root; // Root of the AVL tree

    // Helper methods
    int getHeight(AVLNode *node) const; // Get height of a node
    int getBalanceFactor(AVLNode *node) const; // Calculate balance factor of a node
    AVLNode *rightRotate(AVLNode *y); // Right rotate a subtree
    AVLNode *leftRotate(AVLNode *x); // Left rotate a subtree
    AVLNode *insertHelper(AVLNode *node, std::string key, int docID, int frequency); // Recursive helper for insertion
    AVLNode *removeHelper(AVLNode *node, std::string key); // Recursive helper for removal
    AVLNode *minValueNode(AVLNode *node); // Find node with minimum key value
    void inorderTraversal(AVLNode* node); // Helper for inorder traversal
    void serialize(AVLNode* node, std::ostringstream& out); // Helper for serialization
    std::vector<DocInfo> search(std::string key); // Search for key, return document info
    std::vector<DocInfo> search(AVLNode *node, std::string key); // Recursive helper for search
    AVLNode* findNode(const std::string& key); // Find a node by key
    AVLNode* findNodeHelper(AVLNode* node, const std::string& key); // Recursive helper for findNode
    bool contains(const std::string& key); // Check if tree contains a key
    bool isEmpty() const; // Check if tree is empty
    bool isBalanced() const; // Check if tree is balanced
    bool isBalanced(AVLNode* node) const; // Check if subtree is balanced
    bool isValidAVLTree() const; // Check if tree is a valid AVL tree
    bool isValidAVLTree(AVLNode* node) const; // Check if subtree is a valid AVL tree
};

#endif // AVL_TREE_H
