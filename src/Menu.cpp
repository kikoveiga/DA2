//
// Created by kikoveiga on 03-05-2023.
//

#include "../headers/Menu.h"

using namespace std;

bool isNumber(const string& s) {
    return all_of(s.begin(), s.end(), ::isdigit);
}

Menu::Menu() {
    command = "0";
    run();
}

void Menu::run() {

    bool running = true;

    while (running) {

        switch(stoi(command)) {

            case 0:
                mainMenu();
                break;

            case 1:
                graphsMenu();
                break;

            case 2:
                exit(0);
        }
    }
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Menu::enterOption(int n) {

    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= n) break;
        else cout << "   -INVALID OPTION" << endl;
    }
}

void Menu::press0ToContinue() {

    while (true) {
        cout << "PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
        if (command == "0") break;
    }
}

void Menu::mainMenu() {

    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                   MAIN MENU                   |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. GRAPHS MENU                                |\n"
         << "| 2. EXIT                                       |\n"
         << "-------------------------------------------------\n";

    enterOption(2);
}

void Menu::graphsMenu() {

    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                  GRAPHS MENU                  |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. CHOOSE A GRAPH                             |\n"
         << "| 2. NUMBER OF GRAPHS                           |\n"
         << "| 3. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    enterOption(3);

    if (command == "1") { // Choose a Graph

    }

    else if (command == "2") {
        cout << "   -NUMBER OF GRAPHS: " << utils.getGraphs().size() << endl;
        cout << endl;
        press0ToContinue();

    }

    else {
        command = "0";
        return;
    }


    command = "1";
}