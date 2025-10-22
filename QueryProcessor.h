#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include "IndexHandler.h"
#include "SearchTerms.h"
#include <string>
#include <vector>

class QueryProcessor {
public:
    QueryProcessor(IndexHandler& indexHandler);

    // Process a query and return document IDs
    std::vector<int> processQuery(const std::string& query);

private:
    IndexHandler& indexHandler;

    // Parses the query into SearchTerms
    SearchTerms parseQuery(const std::string& query);
};

#endif // QUERY_PROCESSOR_H
