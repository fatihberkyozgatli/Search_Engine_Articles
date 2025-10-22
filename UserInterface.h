#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "QueryProcessor.h"
#include <string>

class UserInterface {
public:
    UserInterface(QueryProcessor& queryProcessor, IndexHandler& indexHandler);

    // Start the main interface loop
    void start();

private:
    QueryProcessor& queryProcessor;
    IndexHandler& indexHandler;

    // Method to handle indexing command
    void handleIndexingCommand();

    // Method to handle query command
    void handleQueryCommand();

    // Method to show the main menu and process user input
    void mainMenu();

    // Helper method to get user input
    std::string getInput(const std::string& prompt);
};

#endif // USER_INTERFACE_H
