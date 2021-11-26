#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

void createFileVersion(string fileName, int version);

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required

}

void printCommitMenu(){
    cout << "1. Add File" << endl;
    cout << "2. Remove File" << endl;
    cout << "3. Commit" << endl;
    cout << "4. Checkout" << endl;
    cout << "#> ";
}

void MiniGit::init(int hashtablesize) {
    // if (fs::exists(".minigit")) {
    //     cout << "git already initialized!" << endl;
    //     return;
    // }
    fs::create_directory(".minigit");
    BranchNode* temp = new BranchNode();
    temp->commitID = 0;
    temp->commitMessage = "";
    temp->next = NULL;
    temp->previous = NULL;

    commitHead = temp;

//    commitHead = new BranchNode();
//    commitHead->commitID = 0;
//    commitHead->fileHead = NULL;
//    commitHead->previous = NULL;
}

void MiniGit::add(string fileName) {
    ifstream myfile;
    myfile.open(fileName);

    while (!myfile.is_open()) {
        cout << "Enter a valid file name: ";
        cin >> fileName;
        myfile.open(fileName);
    }

    BranchNode* latest = commitHead;
    int version = 0;

    while (latest->previous != NULL) {
        latest = latest->previous;
    }

    while (latest->next != NULL) {
        FileNode* curr = latest->fileHead;
        while (curr != NULL) {
            if (curr->name.substr(0, fileName.size()) == fileName) {
                version++;
            }
            curr = curr->next;
        }

        latest = latest->next;
    }

    FileNode* curr = latest->fileHead;
    cout << "CHECKING THE LATEST" << endl;

    while (curr != NULL) {
        cout << curr->name << endl;
        if (curr->name == fileName) {
            cout << "A file by the same name cannot be added twice!" << endl;
            return;
        }
        curr = curr->next;
    }

    string ver = "";

    if (version < 10) {
        ver += "0" + to_string(version);
    } else {
        ver = to_string(version);
    }

    FileNode* temp = new FileNode();
    temp->name = fileName;
    temp->version = version;
    temp->next = NULL;

    if (latest->fileHead == NULL) {
        latest->fileHead = temp;
    } else {
        curr = latest->fileHead;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = temp;
    }

    cout << temp->name << " was added to the SLL as version: " << to_string(temp->version) << endl;

    curr = latest->fileHead;
    cout << "Current files are: ";
    while (curr != NULL) {
        cout << curr->name << " ";
        curr = curr->next;
    }
    cout << endl;
}

FileNode* rmHelper(FileNode* ptr, string fileName, bool & removed){
    if(ptr->name == fileName){
        FileNode* next = ptr->next;
        delete ptr;
        removed = true;
        return next;
    }
    else if(ptr->next){
        ptr->next = rmHelper(ptr->next, fileName, removed);
        return ptr;
    }else{
        return NULL;
    }
}

void MiniGit::rm(string fileName) {
    FileNode* SLL = commitHead->fileHead;
    bool removed = false;
    commitHead->fileHead = rmHelper(SLL, fileName, removed);

    if(removed) cout << "Removed " << fileName << endl;
    else cout << "File not found." << endl;
}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
}

void MiniGit::printCommits(){
    BranchNode* commit = commitHead;

    if(commit){
        while(commit->previous){
            commit = commit->previous;
        }
    }else{
        cout << "Commit history empty." << endl;
        return;
    }

    while(commit && commit->commitMessage.length() > 0){
        cout << commit->commitMessage << "(";

        FileNode* SLL = commit->fileHead;
        while(SLL){
            cout << SLL->name << "[" << SLL->version << "], ";
            SLL = SLL->next;
        }
        cout << ") => ";

        commit = commit->next;
    }
    cout << endl;
}

bool MiniGit::isUniqueCommitMessage(string msg){
    BranchNode* ptr = commitHead;

    //Check commit head
    if(ptr->commitMessage == msg) return false;
    
    //Search backwards from commit head
    BranchNode* prev = ptr->previous;
    while(prev != NULL){
        if(prev->commitMessage == msg) return false;
        prev = prev->previous;
    }

    //Search forwards from commit head
    BranchNode* next = ptr->next;
    while( next != NULL){
        if(next->commitMessage == msg) return false;
        next = next->next;
    }

    return true;
}

FileNode* MiniGit::findExistingVersion(string fileName, int version){
    BranchNode* ptr = commitHead;

    //Start at beginning
    while(ptr->previous != NULL){
        ptr = ptr->previous;
    }

    //Check all commits
    while(ptr){
        if(ptr != commitHead){//Don't check if files exist on current commit
            FileNode* fileptr = ptr->fileHead;

            //Iterate SLL
            while(fileptr){
                //Return true if the file and version is found already (means file should exist already)
                if(fileptr->name == fileName && fileptr->version == version) return fileptr;
            }
        }

        ptr = ptr->next;
    }

    return NULL;
}

void createFileVersion(string fileName, int version){
    string fn = fileName;
    if(version < 10){
        fn = fn + "0";
    }
    fn = fn + to_string(version);

    ifstream infile;
    infile.open(fileName);
    ofstream outfile;
    outfile.open(".minigit/" + fn);

    string line;
    while(getline(infile, line)){
        outfile << line;
    }

    infile.close();
    outfile.close();
}

bool areFilesEqual(FileNode* currVer, FileNode* newVer){
    string currFileName = currVer->name;
    if(currVer->version < 10){
        currFileName += "0"; 
    }
    currFileName += to_string(currVer->version);
    
    ifstream currFile; //File is in .minigit
    currFile.open(".minigit/" + currFileName);

    ifstream newFile;
    newFile.open(newVer->name);

    string currFileStr, newFileStr, a, b;

    while(getline(currFile, a)){
        currFileStr += a;
    }
    while(getline(newFile, b)){
        newFileStr += b;
    }

    cout << currFileStr << endl;
    cout << newFileStr << endl;

    if(currFileStr == newFileStr) return true;
    return false;
}

void copySLL(BranchNode* a, BranchNode* b){
    //Loop through A's SLL
    FileNode* a_iter = a->fileHead;
    while(a_iter){
        FileNode* clone = new FileNode();
        clone->name = a_iter->name;
        clone->version = a_iter->version;

        FileNode* b_iter = b->fileHead;
        if(b_iter){//If not first insert
            while(b_iter->next){//Loop to end of b
                b_iter = b_iter->next;
            }
            b_iter->next = clone;
        }else{ //Else this is the first file inserted
            b->fileHead = clone;
        }

        a_iter = a_iter->next;
    }
}

string MiniGit::commit(string msg) {
    commitHead->commitMessage = msg;

    FileNode* fileptr = commitHead->fileHead;
    while(fileptr){
        FileNode* prevVersion = findExistingVersion(fileptr->name, fileptr->version);

        if(!prevVersion){ //No file exists for this version
            createFileVersion(fileptr->name, fileptr->version);
        }
        else if(!areFilesEqual(fileptr, prevVersion)){//If files are not equal create new version
            //cout << "Files not equal" << endl;
            fileptr->version = fileptr->version + 1;

            createFileVersion(fileptr->name, fileptr->version);
        }else{
            //cout << "Files are equal" << endl;
        }

        fileptr = fileptr->next;
    }

    /**
     * TODO: Need to take all the words and add them to the hash table??
     */
    

    BranchNode* newNode = new BranchNode();
    
    copySLL(commitHead, newNode);

    commitHead->next = newNode;
    newNode->previous = commitHead;
    newNode->commitID = commitHead->commitID + 1;

    commitHead = newNode;

    cout << commitHead->previous->commitMessage;


    return to_string(newNode->commitID); //should return the commitID of the commited DLL node
}

void MiniGit::checkout(string commitID) {
   

}
