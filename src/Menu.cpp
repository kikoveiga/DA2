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

bool Menu::areYouSure() {

    cout << "THIS GRAPH IS A REAL-WORLD GRAPH AND IS VERY BIG!\n";
    cout << "THE RESULT WILL BE PRINTED TO A TEXT FILE\n";

    while (true) {
        cout << "ARE YOU SURE YOU WANT TO PRINT IT? (yes/no) "; getline(cin >> ws, command);
        if (command == "yes" || command == "no") break;
    }

    return command == "yes";
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

        for (int i = 1; i <= utils.getGraphs().size(); i++) {
            cout << "   [" << i << "]" << utils.getGraphs()[i - 1]->getName() << '\n';
        }
        cout << '\n';

        enterOption((int)utils.getGraphs().size());
        graphMenu(utils.getGraphs()[stoi(command) - 1]);
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

void Menu::graphMenu(Graph* graph) {

    cleanTerminal();

    cout << "-------------------------------------------------\n"
         << "|" << setw((int)((42 + (int)graph->getName().size())/2.0)) << graph->getName()<< " MENU"
         << setw(((46 - (int)graph->getName().size())/2.0 + 0.5)) << "|\n"
         << "|-----------------------------------------------|\n"
         << "| 1. NUMBER OF NODES AND EDGES                  |\n"
         << "| 2. PRINT GRAPH                                |\n"
         << "| 3. GO BACK                                    |\n"
         << "-------------------------------------------------\n";


    enterOption(3);

    if (command == "1") { // Number of Nodes and Edges

        cout << "   -NUMBER OF NODES: " << graph->getNodes().size() << '\n';
        cout << "   -NUMBER OF EDGES: " << graph->getNumberOfEdges() << '\n';
        cout << endl;
        press0ToContinue();
    }

    else if (command == "2") { // Print Graph

        if (!graph->isRealOrToy() || areYouSure()) {
            printGraph(graph);
            press0ToContinue();
        }
    }

    else {
        command = "1";
        return;
    }

    graphMenu(graph);

}

void Menu::printGraph(Graph* graph) {

    ofstream file;
    file.open("../dataset/" + graph->getName() + ".txt");

    file << "Nodes = {";

    for (auto i : graph->getNodes()) {
        file << i->id << ", ";
    }

    file.seekp(file.tellp() - (long)2);
    file << "}\n\n";

    file << "Edges = {\n\n";

    for (auto i : graph->getNodes()) {
        file << "   " << i->id << " -> {";
        for (auto j : i->adj) {
             j->first != i ? file << j->first->id << ", " : file << j->second->id << ", ";
        }
        file.seekp(file.tellp() - (long)2);
        file << "}\n";
    }
    file << "}\n";
}