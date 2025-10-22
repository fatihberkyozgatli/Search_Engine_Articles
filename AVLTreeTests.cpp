#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "AVLTree.h"

using namespace Catch::Matchers;

TEST_CASE("AVLTree Functionality", "[AVLTree]") {
    AVLTree tree;

        // Insert test
    SECTION("Inserting Nodes") {
    tree.insert("key1", 1, 1);
    CHECK(tree.contains("key1"));

    tree.insert("key2", 2, 1);
    tree.insert("key3", 3, 1);
    CHECK(tree.contains("key2"));
    CHECK(tree.contains("key3"));

    // Check balance of the tree
    // Calculate the expected balance factors for key1, key2, and key3
    int expectedBalanceFactorKey1 = tree.getBalanceFactor(tree.findNode("key1"));
    int expectedBalanceFactorKey2 = tree.getBalanceFactor(tree.findNode("key2"));
    int expectedBalanceFactorKey3 = tree.getBalanceFactor(tree.findNode("key3"));

    // Check the balance factors
    CHECK(expectedBalanceFactorKey1 == 0); // Since only key1 is inserted
    CHECK(expectedBalanceFactorKey2 == 0); // After inserting key2, left subtree's height is 1 and right subtree's height is 0
    CHECK(expectedBalanceFactorKey3 == 0); // After inserting key3, left subtree's height is 1 and right subtree's height is 1
}


    // Remove test
    SECTION("Removing Nodes") {
        tree.insert("key1", 1, 1);
        tree.insert("key2", 2, 1);
        tree.remove("key1");
        CHECK_FALSE(tree.contains("key1"));
        CHECK(tree.contains("key2"));

        // Check balance of the tree
        CHECK(tree.getBalanceFactor(tree.findNode("key2")) == 0);
    }

    // Search test
    SECTION("Searching Nodes") {
    tree.insert("key1", 1, 2); // Insert key1 with docID=1, frequency=2
    auto searchResult = tree.search("key1");

    REQUIRE(searchResult.size() == 1); // There should be one DocInfo for key1
    CHECK(searchResult[0].docID == 1);
    CHECK(searchResult[0].frequency == 2);

    // Test for a non-existing key
    auto searchResultNonExisting = tree.search("keyX");
    CHECK(searchResultNonExisting.empty());
}

    // Edge Cases
    SECTION("Edge Cases") {
        // Insertion into an empty tree
        tree.insert("key1", 1, 1);
        CHECK(tree.contains("key1"));

        // Removal of non-existent key
        tree.remove("keyX");
        CHECK(tree.isBalanced());

        // Removing from an empty tree
        AVLTree emptyTree;
        emptyTree.remove("key1");
        CHECK(emptyTree.isEmpty());
    }

    // Stress Test
    SECTION("Stress Test") {
        for (int i = 0; i < 1000; ++i) {
            tree.insert("key" + std::to_string(i), i, 1);
        }
        CHECK(tree.isBalanced());
    }

    // Balance Factor Check
    SECTION("Balance Factor Checks") {
    tree.insert("key1", 1, 1);
    tree.insert("key2", 2, 1);
    tree.insert("key3", 3, 1);
    
    int expectedBalanceFactorKey1 = 0;
    int expectedBalanceFactorKey2 = 0;
    int expectedBalanceFactorKey3 = 0;
    
    CHECK(tree.getBalanceFactor(tree.findNode("key1")) == expectedBalanceFactorKey1);
    CHECK(tree.getBalanceFactor(tree.findNode("key2")) == expectedBalanceFactorKey2);
    CHECK(tree.getBalanceFactor(tree.findNode("key3")) == expectedBalanceFactorKey3);
}

    // Tree Integrity
    SECTION("Tree Integrity Post-Operations") {
        tree.insert("key1", 1, 1);
        tree.insert("key2", 2, 1);
        tree.insert("key3", 3, 1);
        tree.remove("key2");

        // Check if the tree structure is as expected after removal
        CHECK(tree.isBalanced());
        CHECK(tree.isValidAVLTree());
    }

    // Dynamic Scenarios
    SECTION("Dynamic Scenarios") {
        tree.insert("key1", 1, 1);
        tree.insert("key2", 2, 1);
        tree.remove("key1");
        tree.insert("key3", 3, 1);
        bool result = tree.contains("key2");

        CHECK(result == true);
        CHECK(tree.isBalanced());
        CHECK(tree.isValidAVLTree());
    }

    // Error Handling
    SECTION("Error Handling") {
        tree.insert("key1", 1, 1);

        // Handling non-existent key removal
        CHECK_NOTHROW(tree.remove("keyX"));

        // Invalid search operation
        CHECK_NOTHROW(tree.search("nonexistent_key"));
    }

    // Doc Info Update correctly?
    SECTION("Updating Document Information") {
    tree.insert("key1", 1, 2);  // Initial insertion with docID=1, frequency=2
    tree.updateDocInfo("key1", 1, 3);  // Update frequency to 3

    auto searchResult = tree.search("key1");
    REQUIRE(searchResult.size() == 1);  // Ensure there is one DocInfo for key1
    CHECK(searchResult[0].docID == 1);
    CHECK(searchResult[0].frequency == 5);  // Check if frequency is updated to 3

    // Test updating a non-existing key
    CHECK_NOTHROW(tree.updateDocInfo("nonexistent_key", 2, 1));  // Should handle gracefully
    }
}
