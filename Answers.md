# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members:




Used free extension: [ ] 24 hrs or [x] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with 
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Planned Week | Task | Planned for... | Completed on... |
|---|---|---|---|
| **1** | Planning/ Design | 5/11 | 5/11 |
| **1** | AVL tree adaptation for the inverted file index | 9/11 | 10/11 |
| **1** | Test AVL-based map | 10/11 | 12/11 |
| **2** | Implement *DocumentParser* | 14/11 | 16/11 |
| **2** | Implement *IndexHandler* | 14/11 | 20/11 |
| **3** | Implement *QueryProcessor* | 20/11 | 30/11 |
| **3** | Create *User Interface* | 22/11 | 1/12 |
| **4** | Debugging and Testing | 29/11 | 2/12 |
| **4** | Cleaning and Finalizing | 2/12 | 3/12 |


### Final Design of Project: 

#### a) Classes:
1. **Document**: Represents a single document.
MetaData: Holds metadata for a document.
2. **ParsedDocument**: Represents a processed document, including token frequencies and entities.
3. **DocumentParser**: Parses documents and updates indices.
4. **IndexHandler**: Manages the indexing of documents and querying.
5. **QueryProcessor**: Processes search queries.
6. **UserInterface**: Handles user interaction with the search engine.
7. **AVLTree**: Data structure for storing and retrieving document indices.
8. **AVLNode**: Represents a node in the AVL Tree.
9. **Stemmer**: Utility for stemming words.
10. **StopwordRemover**: Utility for removing stopwords.

#### b) Interaction Summary:
 These classes work together to create a system where documents are parsed, indexed, and made searchable. The DocumentParser processes documents into a format suitable for indexing. The IndexHandler takes these processed documents to build and maintain indices. QueryProcessor uses these indices to find relevant documents based on user queries, and the UserInterface acts as the bridge between the user and the search engine's functionality.
#### c) Pseudocode:
##### 1. Document Parsing:
- Read file content.
- Create a Document object.
- Use DocumentParser to parse the document.
- Update the AVL Tree with token frequencies.

##### 2. Indexing Documents
- For each document in the directory:
    - Read and parse the document.
    - Update word indices, org indices, and person indices.

##### 3. Query Processing
- Receive a query.
    - If the query is for an organization or person, use the respective index.
    - Otherwise, search the AVL Tree for relevant documents.
- Sort documents based on relevance scores.

##### 4. User Interaction
- Present options to the user (index, query, exit).
- Handle user input and call appropriate functions.

### Used Data Structures

#### 1. AVL Tree (used in IndexHandler for wordIndex)

- Complexity:
    - Time: O(log n) for insertion, deletion, and search.
    - Space: O(n) for storing n keys.
- Reason for Choice: The AVL Tree maintains a balanced binary search tree, ensuring O(log n) complexity for operations, which is crucial for efficient indexing and searching. It's especially effective for datasets that frequently change.

#### 2. Unordered Map (used in IndexHandler for orgIndex and personIndex)

- Complexity:
    - Time: Average O(1) for search, insertion, and deletion. Worst-case O(n).
    - Space: O(n) for storing n key-value pairs.
- Reason for Choice: Unordered maps provide fast access, insertion, and deletion of elements based on keys. They are hash tables and are efficient for lookup operations.

#### 3. Vector (used in various places like storing document IDs)

- Complexity:
    - Time: O(1) for accessing elements, O(n) for inserting or deleting at the end, O(n) for inserting or deleting in the middle.
    - Space: O(n) for storing n elements.
- Reason for Choice: Vectors are dynamic arrays that are efficient for accessing elements and provide good performance for adding or removing elements at the end.

#### 4. Set (used in IndexHandler for storing unique document IDs in orgIndex and personIndex)

- Complexity:
    - Time: O(log n) for insertions, deletions, and searches.
    - Space: O(n) for storing n elements.
R- eason for Choice: Sets are useful for maintaining a collection 

### User Documentation

#### 1. Features of the Software
- Indexing: Indexes documents from a specified directory, creating a searchable data structure.
- Search Queries: Supports searching the indexed data using keywords. It can handle both regular text and specific queries for organizations or persons.
- Ranking and Sorting: Search results are ranked based on their relevance (frequency of the search term in the document).
- Top Results: Displays the top 10 most relevant search results.
- Entity Recognition: Identifies and indexes specific entities like organizations and persons.
- Performance Metrics: Displays the time taken for indexing operations.
- Most Frequent Term: Identifies and displays the most frequently used term in the indexed documents. (will be implemented)
- Saving and Loading Index: Allows the user to save the indexed data to a file and load it later.

#### 2. How to Use the Software
- Starting the Software: Run ./supersearch in the command line.

- Main Commands:

    - **index**: Indexes documents from a specified directory.
    - **query**: Performs a search query.
    - **exit**: Exits the program.

        - Indexing Documents:
            - Select the index command.
            - Enter the directory path containing the documents to be indexed.
            - Optionally, save the index to a file when prompted.
        - Performing Search Queries:
            - Select the query command.
            - Enter your search term. For specific entity queries, use the format ORG:<organization name> or PERSON:<person's name>.
            - View the top 10 search results, including document ID, path, and title.

#### 3. Example Queries (with Performance Displayed): 

1.
- I: 
% ./supersearch 
- O: 
Commands:
  index - Index a directory
  query - Perform a search query
  exit  - Exit the program
Enter your choice: 
- I: 
index
- O: 
Enter directory path: 
- I: 
/Users/fatihberkyozgatli/Desktop/CS 2341/assignment-4-search-engine-fatih-berk/archive/2018_04_112b52537b67659ad3609a234388c50a
- O: 
Indexing documents from directory: /Users/fatihberkyozgatli/Desktop/CS 2341/assignment-4-search-engine-fatih-berk/archive/2018_04_112b52537b67659ad3609a234388c50a
Indexing completed successfully.
Indexing completed in 235 seconds.
Save index to file? (yes/no): 
- I: 
yes
- O: 
Enter file path to save index: 
- I: 
./data
- O: 
Index saved successfully.

2.
- O:
Commands:
  index - Index a directory
  query - Perform a search query
  exit  - Exit the program
Enter your choice: 
- I:
query
- O: 
Enter search query: 
- I:
Report
- O:
Top 10 documents with IDs (or less if fewer results): 46460 32450 42150 38982 3114 33984 53823 38270 15997 45487



