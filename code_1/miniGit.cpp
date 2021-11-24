#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

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

    /*
   int choice = -1;
   cin >> choice;

   printCommitMenu();

   switch(choice){
        case 1: //Add a file
            break;
        case 2:
            break;
        case 3: 
            break;
        case 4:
            break;
        default:
            cout << "That is not an option."
            
   }
   */
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

void MiniGit::rm(string fileName) {
    cout << "Enter file name\n#> ";
    string filename;
    cin >> filename;

    FileNode* SLL = commitHead->fileHead;
    if(SLL->name == fileName){ //Is first element the head?
        FileNode*  tmp = SLL;
        commitHead->fileHead = SLL->next;
    }

    while(true){
        
    }
}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
}



string MiniGit::commit(string msg) {
    return " "; //should return the commitID of the commited DLL node
}

void MiniGit::checkout(string commitID) {
   

}
