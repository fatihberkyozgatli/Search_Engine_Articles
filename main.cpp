#include "QueryProcessor.h"
#include "UserInterface.h"

int main() {
    IndexHandler indexHandler;
    QueryProcessor queryProcessor(indexHandler);
    UserInterface ui(queryProcessor, indexHandler);

    ui.start();

    return 0;
}
