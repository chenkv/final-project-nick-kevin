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
    int option = 0;
    MiniGit git;

    while (true) {
        displayMenu();
        cin >> option;

        switch (option) {
            case 1:

                break;
            
            case 2: {
                string name;
                cout << "Enter a file name: ";
                cin >> name;
                git.add(name);
                break;
            }

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

            case 6:

                break;
            
            case 7:
                return 0;
                break;
            
            default:
                return 0;
                break;
        }
    }
   
    return 0;
}