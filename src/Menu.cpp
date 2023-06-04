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
                algorithmsMenu();
                break;

            case 3:
                tSPGameMenu();
                break;

            case 4:
                exit(0);
        }
    }
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Menu::enterOption(unsigned n) {

    cout << '\n';
    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= n) break;
        else cout << "   -INVALID OPTION" << "\n\n";
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
         << "| 2. ALGORITHMS MENU                            |\n"
         << "| 3. TSP GAME MENU                              |\n"
         << "| 4. EXIT                                       |\n"
         << "-------------------------------------------------\n";

    enterOption(3);
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

        cout << "\n   -CHOOSE A GRAPH:\n";
        for (int i = 1; i <= utils.getGraphs().size(); i++) {
            cout << "      [" << i << "]" << utils.getGraphs()[i - 1]->getName() << '\n';
        }

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
         << "| 2. IS IT COMPLETE AND/OR CONNECTED?           |\n"
         << "| 3. PRINT GRAPH                                |\n"
         << "| 4. GO BACK                                    |\n"
         << "-------------------------------------------------\n";


    enterOption(4);

    if (command == "1") { // Number of Nodes and Edges

        cout << "This graph has " << graph->getNodes().size() << " nodes and " << graph->getNumberOfEdges() << " edges.\n";
        cout << endl;
        press0ToContinue();
    }

    else if (command == "2") { // Is it complete and/or connected?

        cout << "   -This graph is " << (graph->isComplete() ? "" : "not ") << "complete and is" << (graph->isConnected() ? "" : "not ") << "connected.\n";
        cout << endl;
        press0ToContinue();
    }

    else if (command == "3") { // Print Graph

            printGraph(graph);
            cout << "   -The graph has been printed in the folder 'dataset/prints'.\n";
            cout << endl;
            press0ToContinue();
    }

    else {
        command = "1";
        return;
    }

    graphMenu(graph);

}

void Menu::printGraph(Graph* graph) {

    ofstream file;
    file.open("../dataset/prints/" + graph->getName() + ".txt");

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

void Menu::algorithmsMenu() {

    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                ALGORITHMS MENU                |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. TSP BACKTRACKING                           |\n"
         << "| 2. TSP 2APPROXIMATION HEURISTIC               |\n"
         << "| 3. TSP NEAREST NEIGHBOR HEURISTIC             |\n"
         << "| 4. TSP GREEDY HEURISTIC                       |\n"
         << "| 5. TSP 1TREE LOWER BOUND                      |\n"
         << "| 6. CHRISTOFIDES HEURISTIC                     |\n"
         << "| 7. APPLY ALL ALGORITHMS                       |\n"
         << "| 7. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    enterOption(7);

    if (command == "1") { // TSP Backtracking


    }


    command = "2";
}

void Menu::tSPGameMenu() {

    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 TSP GAME MENU                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. CHOOSE A GRAPH                             |\n"
         << "| 2. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    enterOption(2);

    if (command == "1") { // Choose a Graph

        cout << "\n   -CHOOSE A GRAPH:\n";
        for (int i = 1; i <= 2; i++) {
            cout << "      [" << i << "]" << utils.getGraphs()[i]->getName() << '\n';
        }

        enterOption(2);
        tSPGame(utils.getGraphs()[stoi(command)]);
    }

    else {
        command = "0";
        return;
    }

    command = "3";
}

void Menu::tSPGame(Graph* graph) {

    cleanTerminal();

    vector<unsigned> path;
    path.push_back(0);

    auto nodes = graph->getNodes();
    unsigned currNode = 0;
    nodes[0]->visited = true;
    double distance = 0;

    while (true) {

        cleanTerminal();

        if (path.size() == nodes.size() + 1) { // Game ends
            cout << "   -Path:";
            for (auto i : path) {
                cout << ' ' << i << " ->";
            }
            cout << "\b\b  " << endl;
            cout << "   -Distance: " << distance << endl;
            cout << "   -You have visited all nodes!\n";
            cout << endl;
            graph->setAllNodesUnvisited();
            press0ToContinue();
            return;
        }

        cout << "   -Path:";
        for (auto i : path) {
            cout << ' ' << i << " ->";
        }
        cout << "\b\b  " << endl;
        cout << "   -Distance: " << distance << endl;

        cout << "\nChoose a node to visit: \n";

        vector<unsigned> options;
        for (auto i : nodes[currNode]->adj) {
            unsigned next = currNode == i->first->id ? i->second->id : i->first->id;

            if ((path.size() != nodes.size() && next != 0 && !nodes[next]->visited) || (path.size() == nodes.size() && next == 0)) {

                options.push_back(next);
                cout << "   [" << next << ']' << " Distance: " << i->distance << endl;
            }
        }

        cout << endl;
        while (true) {
            cout << "   -OPTION: "; getline(cin >> ws, command);
            if (isNumber(command) && find(options.begin(), options.end(), stoi(command)) != options.end()) break;
            cout << "   -INVALID OPTION\n\n";
        }

        path.push_back(stoi(command));
        nodes[stoi(command)]->visited = true;
        distance += graph->findEdge(currNode, stoi(command))->distance;
        currNode = stoi(command);
    }
}