#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
#include <string>

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
        /*
        int option = 1;
        displayMenu();
        cin >> option;
        */
        int option = -1;
        string str;
        displayMenu();
        getline(cin, str);
        if(str.length() == 1 && isdigit(str[0])) option = stoi(str);


        switch (option) {
            case 1:{
                git.init(5);
                break;
            }
            case 2: {
                if (!git.isLatestBranch()) {
                    cout << "You can only add to the latest branch!" << endl;
                } else {
                    string name;
                    cout << "Enter the filename to be added:\n#> ";
                    getline(cin, name);
                    git.add(name);
                }
                break;
            }

            case 3:{
                if (!git.isLatestBranch()) {
                    cout << "You can only remove on the latest branch!" << endl;
                } else {
                    cout << "Enter file name\n#> ";
                    string filename;
                    getline(cin, filename);

                    git.rm(filename);
                }
                break;
            }
            case 4: {
                
                string msg = "";
                cout << "Enter unique commit message\n#> ";
                getline(cin, msg);

                if(!git.isUniqueCommitMessage(msg)){
                    while(!git.isUniqueCommitMessage(msg)){
                        cout << "Enter unique commit message\n#> ";
                        getline(cin, msg);
                    }
                }

                git.commit(msg);

                break;
            }
            case 5: {
                string idstr;
                int id = -1;
                do {
                    cout << "Enter a commit number to checkout\n#> ";
                    getline(cin, idstr);
                    if(idstr.length() == 1 && isdigit(idstr[0])) id = stoi(idstr);

                } while (!git.isValidCommitID(id));

                git.checkout(to_string(id));

                break;
            }
            case 6: {
                string key;
                cout << "Enter Search Key\n#> ";
                //cin >> key;
                getline(cin, key);

                git.search(key);
                break;
            }
            case 7: {
                return 0;
                break;
            }
            default: {
                cout << "Improper choice" << endl;
                /*
                displayMenu();
                cin >> option;
                */
                //cin.clear();
                break;
            }
        }
    }
   
    return 0;
}