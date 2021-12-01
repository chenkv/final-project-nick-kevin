# CSCI 2275 – Data Structures - Final Project

**Team members:** Nicholas Henley, Kevin Chen

## Summary

This project is designed to be a mini version of git as a file version control system. The user can add and delete files to keep track of. Then, each commit branch is stored in a double linked list. Each file of each version is stored as a singly linked list that each node in the doubly linked list points to. As updates are created and committed, past file versions are stored in the .minigit directory. The user is then able to retrieve past version of files by "checking" them out. With each commit is a commit message which is stored in a hash table. The user is also able to search the commits to find which commits contain the matching keyword in their commit message.

## main_1.cpp
      
This is the main executable of this program. The user interface with the git program is located here.

### *displayMenu()*

This method prints to the console every possible option for the user to choose from.

### *main()*

This is the main method that runs during execution. It initializes a MiniGit object. Then, it continuously loops forever to collect the correct user input and execute the corresponding method to what the user is trying to do. Any improper choice continues the loop and choosing option 7 quits the program. The options correspond to the choices displayed in *displayMenu()*.


## miniGit.hpp

Provides the basic functions and structure of the MiniGit class. MiniGit has a pointer to the current commit number, a hashtable, and an int to keep track of the number of commits. Also includes the structs for **FileNode** which is used for the singly linked list in each commit version to keep track of each file and **BranchNode** which is used for the doubly linked list to keep track of each commit.

## miniGit.cpp

This is where each function is defined of MiniGit, including adding, committing, etc.

### *MiniGit()*

This constructor clears the minigit folder of files to prepare for the new intance of git. The minigit folder contains the version of each file from the commits.

### *init(int hashtablesize)*

If the user chooses to initialize git, this method will be called. First, it checks if git was already initialized by seeing if the *.minigit* folder was already created. Then, it creates a new *.minigit* directory. After, it creates a new BranchNode with no values and no files and sets it as the latest branch pointer for commitHead. It then initializes a hash table of the desired size.

### *add(string fileName)*

If the user chooses to add a file, this method will be called. Using the filename, it first checks to see if the filename leads to a proper file. If not, it will continue to prompt the user for a correct filename. Then, since commitHead doesn't necessarily point to the latest branch, only the current branch, a new pointer is created and then looped to point to the latest branch version. Then, a FileNode pointer loops through the latest branch's singly linked list to see if the file name trying to be added is a duplicate. If so, the program exits the add function. Otherwise, a new file of the user input's filename is created and added to the end of the current branch's singly linked list.

### *rmHelper(FileNode* ptr, string fileName, bool & removed)*

This method is the helper function for the remove function if the user decides to remove a file. This method recursively searches the singly linked list for the desired file name and removes that file from the linked list of files.

### *rm(string fileName)*

If the user chooses to delete a file, this method will be called. It first checks to see if git is even initialized. If not, the function exits. Otherwise, it calls *rmHelper()* on the head of the singly linked list with the filename provided by the user. Then, if the file was removed, it displays that the file was removed. Otherwise, an error is printed.

### *printSearchTable()*

Calls the hashtable's print function.

### *search(string key)*

If the user chooses to search the commits for a keywor, this method will be called. It calls the hashtable's *searchItem()* function with the user inputted key. Then, with the pointer to the keyword, it loops through the pointer to print all the commits the keyword was found in. Otherwise, it prints an error.

### *printCommits()*

This function prints all the current commits. Used during testing.

### *isUniqueCommitMessage(string msg)*

This method is called whenever the user is trying to commit and is typing in a commit message. Commit messages must be unique, so this function returns whether a message has been used already or not. It loops through each commit to check and see if the msg property of each BranchNode already has the same commit message. If so, false is returned. Otherwise, true is returned.

### *findExistingVersion(string fileName, int version)*

This method is called when the user chooses to commit the current branch. This function returns the FileNode of the desired version of a given filename. It loops through each commit branch from the beginning and returns the FileNode with the matching name and version if found. Otherwise, NULL is returned.

### *createFileVersion(string fileName, int version)*

This method is called during commit. If a new file needs to be created, it takes in a filename and version. Then, it creates the appropriate file with the filename and version. It then opens the current file in the user's directory and copies each line over to the new committed file version.

### *areFilesEqual(FileNode* currVer, FileNode* newVer)*

This method is called during commit. This checks to see if a current version of the file in the latest branch is the same as the previous version. It opens both these files and checks to see if the content of the files are the same. If so, true is returned. Otherwise, the function returns false.

### *copySLL(BranchNode* a, BranchNode* b)*

This method is called during commit. After a commit, a new branch for the current version is created. This function copies the contents of the singly linked list of files from BranchNode a to BranchNode b. It loops through each node in the singly linked list of a, creates a copy, and adds it to the singly linked list of b.

### *splitString (string msg)*

This method is called during commit. It splits the input string into each word and returns them in a vector of strings. It loops through the string, finds each space, then pushes to the vector a substring from the start of the word to the end of the word.

### *commit(string msg)*

If the user chooses to commit the latest branch, this method is called. The function takes in a valid message from the user. It first finds the latest branch. Then, it checks to see if a previous version of the file exists. If not, then a new file is created in the .minigit directory with the file name and version. Otherwise, it checks to see if the current file and previous file are equal. If they are not, then a new file of the name is created but with the next version. It then loops through each file in a similar manner in the singly linked list. Then, for the message, it splits the message into each word. It then inserts each word into the hashtable including its commitID. A new BranchNode is then created, the previous version's singly linked list of files copied over, its version one higher, and previous set to the last commit. commitHead is then set to this latest branch. The function then returns the latest commitID.

### *isValidCommitID(int id)*

This method is used in *main_1.cpp*. As the user inputs a commit id, this method checks to see if there is a commit with the same commit id. If so, true is returned. False is returned otherwise.

### *checkout(string commitID)*

If the user chooses to checkout a commit version, this method is called. It takes in a valid commitID. It first confirms with the user if they are willing to lose their current changes. Then, the function removes each file of the matching singly linked list file in the user's directory. Then, the function loops to the corresponding commit with the matching ID. It then loops through each file in the singly linked list of that commit, copies the content of that file into a new file in the user's directory, and repeats for each file.

### *isLatestBranch()*

This method is used in *main_1.cpp* to check for valid input. If the user tries to add or remove or commit on a previous older version branch, they will be denied. This function checks to see if commitHead points to the latest branch version. If so, it returns true. Otherwise, false is returned.

## hash.hpp

This provides the basic structure and functionality of the hashtable. It provides a struct of HashNode which keeps track of each key and the commit numbers that they are found in. It then points to the next HashNode. The functions of the HashTable are then declared and it points to an array containing buckets.

## hash.cpp

This file defines the hashtable's functions.

### *HashTable(int bsize)*

This constructor creates the hashtable of the desired size. An array for each bucket is created and set to NULL.

### *createNode(string key, HashNode* next)*

This function returns an empty HashNode.

### *hashFunction(string s)*

This function calculates the index for the desired string. The index is calculated by taking in the string, adding the value of each character, taking the value modulo 5, and then returning that value.

### *searchItem(string key)*

This function searches and returns the HashNode of the desired key. It first gets the index of the key and returns the corresponding HashNode of that key. If it's not found, NULL is returned.

### *insertItem(string key, int cNum)*

This function inserts a key into the hashtable. It first retrieves the key. Then adds the commit version to the end of commitNums of the found key. It then finds the index of the key. A new HashNode is then created of the input values of key and commit number, then it is added to the hashtable with the calculated index. True is returned if successful, false otherwise.

### *printTable()*

This function prints the hashtable. It loops through each index of the hashtable, prints each key, and each commit that the key is found in. Mostly used in testing.

## test.cpp

This file is where the tests for the project are found. There are many test cases here, which when compiled with "cmake .." and "make" and then ran with "./run_tests" returns the success of the test cases. Each test tests the functionality of different parts of the hashtable, checks to see if the desired result is achieved, then adds a score.

## test_helpers.hpp

Declares the functions to be used during testing.

## test_helpers.cpp

Test helper functions are here.

### *test_insert(string arr[], int len, int tabSize)*

This helper helps test the insert function of the hashtable. It takes an array of commits, loops through and adds each to the hashtable, then prints the table and returns that output.

### *test_search(string arr[], int len, int tabSize, string search)*

This helper tests the search function. It takes in an array of commits, adds them to the hashtable, prints the table, searches for the desired string, and prints out the matching key and the commit IDs that the key is found in. The output is then returned.
