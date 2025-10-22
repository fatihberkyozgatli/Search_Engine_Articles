#include "AVLTree.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>

// Constructor for DocInfo structure
DocInfo::DocInfo(int id, int freq) : docID(id), frequency(freq) {}

// Constructor for AVLNode
AVLNode::AVLNode(std::string k, int docID, int freq) : key(k), left(nullptr), right(nullptr), height(1) {
    addDocInfo(docID, freq); // Initialize with document info
}

// Find method in AVLNode
AVLNode* AVLNode::find(const std::string& key) {
    if (key == this->key) {
        return this;
    } else if (key < this->key && left != nullptr) {
        return left->find(key);
    } else if (key > this->key && right != nullptr) {
        return right->find(key);
    }
    return nullptr;
}

// Destructor
AVLTree::~AVLTree() {
    destroyTree(root);
}

// Remove tree
void AVLTree::destroyTree(AVLNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Adds document information to a node
void AVLNode::addDocInfo(int docID, int frequency) {
    auto it = std::find_if(docList.begin(), docList.end(), 
                           [docID](const DocInfo& info) { return info.docID == docID; });

    if (it != docList.end()) {
        it->frequency += frequency;
    } else {
        docList.emplace_back(docID, frequency);
    }
}


// Constructor for AVLTree
AVLTree::AVLTree() : root(nullptr) {}

// Inserts a new key into the AVL tree
void AVLTree::insert(std::string key, int docID, int frequency) {
    root = insertHelper(root, key, docID, frequency); // Call to helper method
}

// Removes a key from the AVL tree
void AVLTree::remove(std::string key) {
    root = removeHelper(root, key); // Call to helper method
}

// Serializes the AVL tree into a string
std::string AVLTree::serialize() {
    std::ostringstream out;
    out << "["; // Start JSON array
    serialize(root, out);
    out << "]"; // End JSON array
    return out.str();
}

// Deserializes a string to reconstruct the AVL tree
void AVLTree::deserialize(const std::string& data) {
    std::istringstream in(data);
    std::string key;
    int docID, frequency;

    while (in >> key >> docID >> frequency) {
        // Validate input format
        if (key.empty() || docID < 0 || frequency < 0) {
            std::cerr << "Invalid data format in deserialize operation." << std::endl;
            continue;  // Skip invalid line
        }
        insert(key, docID, frequency);
    }

    // Check for deserialization errors
    if (in.fail() && !in.eof()) {
        std::cerr << "Error occurred while deserializing data." << std::endl;
    }
}

// Updates the document information for a specific key
void AVLTree::updateDocInfo(std::string key, int docID, int newFrequency) {
    // Validate input
    if (key.empty() || docID < 0 || newFrequency < 0) {
        std::cerr << "Invalid input for updateDocInfo operation." << std::endl;
        return;
    }
    AVLNode* node = findNode(key);
    // Update information if key is found
    if (node) {
        node->addDocInfo(docID, newFrequency);
    } else {
        std::cerr << "Key not found for update operation." << std::endl;
    }
}

// Find Node method
AVLNode* AVLTree::findNode(const std::string& key) {
    return findNodeHelper(root, key);  // Start the search from the root using the helper function
}

// Recursive helper for findNode
AVLNode* AVLTree::findNodeHelper(AVLNode* node, const std::string& key) {
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;
    return key < node->key ? findNodeHelper(node->left, key) : findNodeHelper(node->right, key);
}

// Gets the height of a given node
int AVLTree::getHeight(AVLNode *node) const {
    return node ? node->height : 0;
}

// Calculates the balance factor of a node
int AVLTree::getBalanceFactor(AVLNode *node) const{
    return getHeight(node->left) - getHeight(node->right);
}

// Performs a right rotation on the tree
AVLNode* AVLTree::rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    // Rotate nodes
    x->right = y;
    y->left = T2;
    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

// Performs a left rotation on the tree
AVLNode* AVLTree::leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    // Rotate nodes
    y->left = x;
    x->right = T2;
    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Finds the node with the minimum key value in a subtree
AVLNode* AVLTree::minValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Public method for inserting a key into the AVL tree
AVLNode* AVLTree::insertHelper(AVLNode* node, std::string key, int docID, int frequency) {
    if (node == nullptr) {
    return new AVLNode(key, docID, frequency); // Create a new node with key, docID, and frequency
    }
    // Recursive insertion in the correct subtree
    if (key < node->key) {
        node->left = insertHelper(node->left, key, docID, frequency);
    } else if (key > node->key) {
        node->right = insertHelper(node->right, key, docID, frequency);
    } else {
        node->addDocInfo(docID, frequency); // Update document info for duplicate keys
        return node;
    }

    // Update the height of this node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Check and correct the balance factor
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return the node pointer (unchanged or updated)
}

// Public method for removing a key from the AVL tree
AVLNode* AVLTree::removeHelper(AVLNode* node, std::string key) {
    if (node == nullptr) {
        return nullptr; // Key not found, return null
    }

    // Finding the node to be deleted
    if (key < node->key) {
        node->left = removeHelper(node->left, key);
    } else if (key > node->key) {
        node->right = removeHelper(node->right, key);
    } else {
        // Node with the key found, now delete it
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = node->left ? node->left : node->right;

        // Inside removeHelper function
        if (temp == nullptr) {
            temp = node;
            node = nullptr;
        } else {
            *node = *temp;
            temp->left = nullptr;  // Avoid deleting the subtree
            temp->right = nullptr; // Avoid deleting the subtree
        }

delete temp;  // Free the memory of the removed node

            delete temp;
        } else {
            // Node with two children: get the inorder successor
            AVLNode* temp = minValueNode(node->right);

            // Copy the inorder successor's data to this node and delete the successor
            node->key = temp->key;
            node->docList = temp->docList;
            node->right = removeHelper(node->right, temp->key);
        }
    }

    if (node == nullptr) {
        return nullptr;
    }

    // Update the height of the current node and balance the tree
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Check and correct the balance
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        return rightRotate(node);
    }

    // Left Right Case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        return leftRotate(node);
    }

    // Right Left Case
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return the (possibly updated) node pointer
}

// Public method for searching a key in the AVL tree
std::vector<DocInfo> AVLTree::search(std::string key) {
    std::vector<DocInfo> result = search(root, key);
    if (result.empty()) {
        // Handle the case where the key is not found
        std::cerr << "Key not found: " << key << std::endl;
    }
    return result;
}

// Helper method for searching a key in the AVL tree
std::vector<DocInfo> AVLTree::search(AVLNode *node, std::string key) {
    if (node == nullptr) {
        return std::vector<DocInfo>();  // Return empty vector if key not found
    }
    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    } else {  // Key found
        return node->docList;
    }
}

// Performs an inorder traversal of the AVL tree
void AVLTree::inorderTraversal() {
    inorderTraversal(root);  // Call to the helper method
    std::cout << std::endl;
}

// Helper method for inorder traversal
void AVLTree::inorderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left);
    // Process the node's data
    inorderTraversal(node->right);
}


// Helper method for JSON serialization
void AVLTree::serialize(AVLNode* node, std::ostringstream& out) {
    if (node == nullptr) {
        return; // Do nothing for null nodes
    } else {
        // Serialize the current node
        out << "{\"key\":\"" << node->key << "\", \"docs\":[";
        for (size_t i = 0; i < node->docList.size(); ++i) {
            out << "{\"docID\":" << node->docList[i].docID << ", \"frequency\":" << node->docList[i].frequency << "}";
            if (i < node->docList.size() - 1) out << ", "; // Add comma between documents
        }
        out << "]}";

        // Serialize left and right subtree if they exist
        if (node->left != nullptr || node->right != nullptr) {
            out << ", "; // Add comma before next node
        }

        serialize(node->left, out); 
        serialize(node->right, out); 
    }
}

    // Checks if a key exists in the AVL tree
    bool AVLTree::contains(const std::string& key) {
    return findNode(key) != nullptr;
    }

    // Checks if the AVL tree is empty
    bool AVLTree::isEmpty() const {
    return root == nullptr;
    }

    // Checks if the AVL tree is balanced
    bool AVLTree::isBalanced() const {
    return isBalanced(root);
    }

    // Helper method to check if a subtree is balanced
    bool AVLTree::isBalanced(AVLNode* node) const {
    if (node == nullptr) {
        return true; // An empty tree is considered balanced
    }

    int balanceFactor = getBalanceFactor(node);

    // Check if the balance factor is within the range [-1, 1]
    if (balanceFactor < -1 || balanceFactor > 1) {
        return false;
    }

    // Recursively check the balance of left and right subtrees
    return isBalanced(node->left) && isBalanced(node->right);  
    }

    // Checks if the AVL tree is a valid AVL tree
    bool AVLTree::isValidAVLTree() const {
    return isValidAVLTree(root);
    }

    // Helper method to check if a subtree is a valid AVL tree
    bool AVLTree::isValidAVLTree(AVLNode* node) const {
    if (node == nullptr) {
        return true; // An empty tree is a valid AVL tree
    }

    // Check if the current node's balance factor is within the range [-1, 1]
    if (getBalanceFactor(node) < -1 || getBalanceFactor(node) > 1) {
        return false;
    }

    // Recursively check the validity of left and right subtrees
    return isValidAVLTree(node->left) && isValidAVLTree(node->right);   
    }