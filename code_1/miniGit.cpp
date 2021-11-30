#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

void createFileVersion(string fileName, int version);
bool areFilesEqual(FileNode* currVer, FileNode* newVer);

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    // fs::create_directory(".minigit");
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
    if (fs::exists(".minigit")) {
        cout << "git already initialized!" << endl;
        return;
    }
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
    BranchNode* temp = new BranchNode();
    temp->commitID = 0;
    temp->commitMessage = "";
    temp->next = NULL;
    temp->previous = NULL;

    commitHead = temp;

    ht = new HashTable(hashtablesize);
}

void MiniGit::add(string fileName) {
    ifstream myfile;
    myfile.open(fileName);

    while (!myfile.is_open()) {
        cout << "Enter a valid file name:\n#> ";
        cin >> fileName;
        myfile.open(fileName);
    }

    BranchNode* latest = commitHead;

    while (latest->previous != NULL) {
        latest = latest->previous;
    }

    while (latest->next != NULL) {
        latest = latest->next;
    }

    FileNode* curr = latest->fileHead;

    while (curr != NULL) {
        if (curr->name == fileName) {
            cout << "The same file cannot be added twice!" << endl;
            return;
        }
        curr = curr->next;
    }

    FileNode* temp = new FileNode();
    temp->name = fileName;
    temp->version = 0;
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
    if (commitHead == NULL) {
        cout << "Not even initialized!" << endl;
        return;
    }

    if (commitHead->fileHead != NULL) {
        FileNode* SLL = commitHead->fileHead;
        bool removed = false;
        commitHead->fileHead = rmHelper(SLL, fileName, removed);

        if(removed) cout << "Removed " << fileName << endl;
        else cout << "File not found." << endl;
    } else {
        cout << "File not found." << endl;
    }
}

void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
    HashNode* ptr = ht->searchItem(key);
    if(ptr != NULL){
        cout << key << " in commit(s): ";
        for(int i = 0; i < ptr->commitNums.size(); i++){
            cout << ptr->commitNums.at(i) << " ";
        }
        cout << endl;
    }
    else{
        cout << "Key not found." << endl;
    }
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
                fileptr = fileptr->next;
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

    if (getline(infile, line)) {
        outfile << line;
    }

    while(getline(infile, line)) {
        outfile << "\n";
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

    if (getline(currFile, a)) {
        currFileStr += a;
    }

    while(getline(currFile, a)){
        currFileStr += "\n";
        currFileStr += a;
    }

    if (getline(newFile, b)) {
        newFileStr += b;
    }

    while(getline(newFile, b)) {
        newFileStr += "\n";
        newFileStr += b;
    }

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

vector<string> splitString (string msg){
    string str = msg;
    vector<string> split;
    
    if(str.find(" ") != string::npos){
        while(str.find(" ") != string::npos){
            split.push_back(str.substr(0, str.find(" ")));
            str = str.substr(str.find(" ") + 1);
        }
        split.push_back(str);
    }
    else{
        split.push_back(msg);
    }

    return split;
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

    //split string
    vector<string> split = splitString(msg);
    for(int i = 0; i < split.size(); i++){
        ht->insertItem(split.at(i), commitHead->commitID);
    }
    
    BranchNode* newNode = new BranchNode();
    
    copySLL(commitHead, newNode);

    commitHead->next = newNode;
    newNode->previous = commitHead;
    newNode->commitID = commitHead->commitID + 1;

    commitHead = newNode;

    return to_string(newNode->commitID); //should return the commitID of the commited DLL node
}

bool MiniGit::isValidCommitID(int id) {
    BranchNode* curr = commitHead;

    while (curr->previous != NULL) {
        curr = curr->previous;
    }

    while (curr != NULL) {
        if (curr->commitID == id) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void MiniGit::checkout(string commitID) {
    string confirm;

    cout << "You will lose your current changes if you checkout before you commit! Type \"confirm\" to continue or \"cancel\" to stop...\n";
    while (confirm != "confirm") {
        cout << "#> ";
        getline(cin, confirm);
    }

    if (confirm == "cancel") {
        cout << "Canceling..." << endl;
        return;
    }

    int id = stoi(commitID);
    BranchNode* curr = commitHead;
    FileNode* looper = curr->fileHead;

    while (looper != NULL) {
        fs::remove(looper->name);
        looper = looper->next;
    }

    while (curr->previous != NULL) {
        curr = curr->previous;
    }

    while (curr->commitID != id) {
        curr = curr->next;
    }

    commitHead = curr;

    cout << "Now on commit number: " << commitHead->commitID << endl;

    looper = curr->fileHead;
    while (looper != NULL) {
        ifstream myfile;
        ofstream output;

        string fn = looper->name;
        if(looper->version < 10){
            fn += "0";
        }
        fn += to_string(looper->version);

        myfile.open(".minigit/" + fn);
        output.open(looper->name, ios::out);

        string line;

        if (getline(myfile, line)) {
            output << line;
        }

        while (getline(myfile, line)) {
            output << "\n"; 
            output << line;   
        }

        output.close();

        looper = looper->next;
    }
}

bool MiniGit::isLatestBranch() {
    if (commitHead->next == NULL) {
        return true;
    }
    return false;
}