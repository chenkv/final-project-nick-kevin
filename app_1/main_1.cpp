#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
int main(int argc, char* argv[]) {
    MiniGit git;

    while (true) {
        int option = 1;
        displayMenu();
        cin >> option;

        switch (option) {
            case 1:
                git.init(5);
                break;
            
            case 2: {
                string name;
                cout << "Enter the filename to be added: ";
                cin >> name;
                git.add(name);
                break;
            }

            case 3:{
                cout << "Enter file name\n#> ";
                string filename;
                cin >> filename;

                git.rm(filename);
                break;
            }
            case 4:{
                string msg;
                do{
                    cout << "Enter unique commit message\n#> ";
                    cin >> msg;
                }while(!git.isUniqueCommitMessage(msg));

                git.commit(msg);

                break;
            }
            case 5:{

                break;
            }
            case 6: {

                break;
            }
            case 7: {
                return 0;
                break;
            }
            case 8: {
                git.printCommits();
                break;
            }
            default: {
                cout << "Improper choice" << endl;
                displayMenu();
                cin >> option;
                break;
            }
        }
    }
   
    return 0;
}