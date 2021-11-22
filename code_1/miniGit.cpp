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
   fs::create_directory(".minigit");
   commitHead = new BranchNode();
   commitHead->commitID = 0;
   commitHead->fileHead = NULL;
   commitHead->previous = NULL;

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
        cout << "Enter a valid file name" << endl;
        cin >> fileName;
        myfile.open(fileName);
    }
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
