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

            case 5:
                return;
        }
    }
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
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

    enterOption(4);
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
         << "| " << left << setw(20) <<  graph->getName() + " MENU" << setw(26) << ' ' << "|\n"
         << "|-----------------------------------------------|\n"
         << "| 1. N OF NODES, EDGES AND ARTICULATION POINTS  |\n"
         << "| 2. IS IT COMPLETE AND/OR CONNECTED?           |\n"
         << "| 3. PRINT GRAPH                                |\n"
         << "| 4. GO BACK                                    |\n"
         << "-------------------------------------------------\n";


    enterOption(4);

    if (command == "1") { // Number of Nodes, Edges and Articulation Points

        cout << "   -This graph has " << graph->getNodes().size() << " nodes, " << graph->getNumberOfEdges() << " edges and " << graph->findArticulationPoints().size() << " articulation points.\n";
        cout << endl;
        press0ToContinue();
    }

    else if (command == "2") { // Is it complete and/or connected?

        cout << "   -This graph is " << (graph->isComplete() ? "" : "not ") << "complete and is " << (graph->isConnected() ? "" : "not ") << "connected.\n";
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
         << "| 7. APPLY ALL ALGORITHMS TO ALL GRAPHS         |\n"
         << "| 8. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    enterOption(8);

    if (command == "1") { // TSP Backtracking

        cout << "   -CHOOSE A GRAPH: (TOY GRAPHS ONLY)\n";

        for (int i = 1; i <= 3; i++) {
            cout << "       [" << i << "]" << utils.getGraphs()[i - 1]->getName() << '\n';
        }
        cout << "       [4] ALL\n";

        enterOption(4);

        cout << endl;
        cout << "---------------------------------TSP BACKTRACKING---------------------------------\n";
        cout << "|   GRAPH  | RESULT |  TIME  |                        PATH                       |" << endl;

        if (command == "4") command = "123";

        for (char i : command) {

            vector<unsigned> path;
            auto start = chrono::high_resolution_clock::now();
            double result = utils.getGraphs()[i - '0' - 1]->solveTSPWithBacktracking(path);
            auto end = chrono::high_resolution_clock::now();
            cout << "| " << left << setw(8) << utils.getGraphs()[i - '0' - 1]->getName() << " | " << left << setw(6) << result << " | "
            << left << setw(7) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << "| {";

            string printPath;
            for (auto node : path) {
                printPath += to_string(node) + ", ";
            }
            printPath += "\b\b} ";
            cout << left << setw(53) << printPath << '|' << endl;

        }
        cout << "----------------------------------------------------------------------------------" << "\n\n";
        press0ToContinue();
    }

    else if (command == "2") { // TSP 2Approximation Heuristic

        cout << "   -CHOOSE A GRAPH: (SHIPPING GRAPH EXCLUDED)\n";
        for (int i = 1; i < utils.getGraphs().size(); i++) {
            cout << "       [" << i << "]" << utils.getGraphs()[i]->getName() << '\n';
        }
        cout << "       [" << utils.getGraphs().size() << "] ALL\n";

        enterOption(utils.getGraphs().size());

        cout << endl;
        cout << "-------------------------TSP 2APPROXIMATION HEURISTIC------------------------\n";
        cout << "|   GRAPH   |    RESULT   |   TIME  |                  PATH                 |" << endl;

        unsigned i;
        if (stoi(command) == utils.getGraphs().size()) i = 1;
        else i = stoi(command);

        for (i; i < utils.getGraphs().size(); (command == to_string(utils.getGraphs().size()) ? i++ : i = utils.getGraphs().size())) {

            vector<unsigned> path;
            auto start = chrono::high_resolution_clock::now();
            double result = utils.getGraphs()[i]->tSP2Approximation(path);
            auto end = chrono::high_resolution_clock::now();
            cout << "| " << left << setw(9) << utils.getGraphs()[i]->getName() << " | " << left << setw(11) << result << " | "
            << left << setw(8) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << "| ";

            if (utils.getGraphs()[i]->getName() == "stadiums" || utils.getGraphs()[i]->getName() == "tourism") {
                string printPath = "{";
                for (auto node : path) {
                    printPath += to_string(node) + ", ";
                }
                printPath += "\b\b}";
                cout << left << setw(41) << printPath << " |" << endl;
            }
            else cout << left << setw(37) << " " << " |" << endl;
        }
        cout << "-----------------------------------------------------------------------------" << "\n\n";
        press0ToContinue();
    }

    else if (command == "3") { // TSP Nearest Neighbor Heuristic

        cout << "   -CHOOSE A GRAPH: (SHIPPING GRAPH EXCLUDED)\n";
        for (int i = 1; i < utils.getGraphs().size(); i++) {
            cout << "       [" << i << "]" << utils.getGraphs()[i]->getName() << '\n';
        }
        cout << "       [" << utils.getGraphs().size() << "] ALL\n";

        enterOption(utils.getGraphs().size());

        cout << endl;
        cout << "------------------------TSP NEAREST NEIGHBOR HEURISTIC-----------------------\n";
        cout << "|   GRAPH   |    RESULT   |   TIME  |                  PATH                 |" << endl;

        unsigned i;
        if (stoi(command) == utils.getGraphs().size()) i = 1;
        else i = stoi(command);

        for (i; i < utils.getGraphs().size(); (command == to_string(utils.getGraphs().size()) ? i++ : i = utils.getGraphs().size())) {

            vector<unsigned> path;
            auto start = chrono::high_resolution_clock::now();
            double result = utils.getGraphs()[i]->tSPNNHeuristic(path);
            auto end = chrono::high_resolution_clock::now();
            cout << "| " << left << setw(9) << utils.getGraphs()[i]->getName() << " | " << left << setw(11) << result << " | "
                 << left << setw(8) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << "| ";

            if (utils.getGraphs()[i]->getName() == "stadiums" || utils.getGraphs()[i]->getName() == "tourism") {
                string printPath = "{";
                for (auto node : path) {
                    printPath += to_string(node) + ", ";
                }
                printPath += "\b\b}";
                cout << left << setw(41) << printPath << " |" << endl;
            }
            else cout << left << setw(37) << " " << " |" << endl;
        }
        cout << "-----------------------------------------------------------------------------" << "\n\n";

        press0ToContinue();
    }

    else if (command == "4") { // TSP Greedy Heuristic

        cout << "   -CHOOSE A GRAPH: (ONLY COMPLETE GRAPHS)\n";
        for (int i = 1; i < utils.getGraphs().size() - 2; i++) {
            cout << "       [" << i << "]" << utils.getGraphs()[i]->getName() << '\n';
        }
        cout << "       [" << utils.getGraphs().size() - 2 << "] ALL\n";

        enterOption(utils.getGraphs().size() - 2);

        cout << endl;
        cout << "-----------------------------TSP GREEDY HEURISTIC----------------------------\n";
        cout << "|   GRAPH   |    RESULT   |   TIME  |                  PATH                 |" << endl;

        unsigned i;
        if (stoi(command) == utils.getGraphs().size() - 2) i = 1;
        else i = stoi(command);

        for (i; i < utils.getGraphs().size() - 2; (command == to_string(utils.getGraphs().size() - 2) ? i++ : i = utils.getGraphs().size() - 2)) {

            vector<pair<unsigned, unsigned>> path;
            auto start = chrono::high_resolution_clock::now();
            double result = utils.getGraphs()[i]->tSPGreedyHeuristic(path);
            auto end = chrono::high_resolution_clock::now();
            cout << "| " << left << setw(9) << utils.getGraphs()[i]->getName() << " | " << left << setw(11) << result << " | "
                 << left << setw(8) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << "| ";

            if (utils.getGraphs()[i]->getName() == "stadiums" || utils.getGraphs()[i]->getName() == "tourism") {
                string printPath = "{";
                unsigned next = 0;
                while (!path.empty()) {

                    printPath += to_string(next) + ", ";
                    for (auto it = path.begin(); it != path.end(); it++) {
                        if ((*it).first == next) {
                            next = (*it).second;
                            path.erase(it);
                            break;
                        }

                        if ((*it).second == next) {
                            next = (*it).first;
                            path.erase(it);
                            break;
                        }
                    }
                }
                printPath += "0}";
                cout << left << setw(37) << printPath << " |";
            }
            else cout << left << setw(37) << " " << " |";
            cout << endl;
        }
        cout << "-----------------------------------------------------------------------------" << "\n\n";
        press0ToContinue();
    }

    else if (command == "5") { // TSP 1Tree Lower Bound

        cout << "   -CHOOSE A GRAPH: \n";
        for (int i = 1; i < utils.getGraphs().size(); i++) {
            cout << "       [" << i << "]" << utils.getGraphs()[i - 1]->getName() << '\n';
        }
        cout << "       [" << utils.getGraphs().size() << "] ALL EXCLUDING GRAPH2 AND GRAPH3\n";

        enterOption(utils.getGraphs().size());

        cout << endl;
        cout << "-----------------------------------------------------------------------TSP 1TREE LOWER BOUND-----------------------------------------------------------------------\n";
        cout << "|   GRAPH   |    RESULT   |    TIME    |                                                           EDGES                                                          |" << endl;

        unsigned i;
        if (stoi(command) == utils.getGraphs().size()) i = 0;
        else i = stoi(command) - 1;

        for (i; i < utils.getGraphs().size() - 2; (command == to_string(utils.getGraphs().size()) ? i++ : i = utils.getGraphs().size() - 2)) {

            vector<pair<unsigned, unsigned>> tree;
            auto start = chrono::high_resolution_clock::now();
            double result = utils.getGraphs()[i]->tSP1TreeLowerBound(tree);
            auto end = chrono::high_resolution_clock::now();
            cout << "| " << left << setw(9) << utils.getGraphs()[i]->getName() << " | " << left << setw(11) << result << " | "
                 << left << setw(10) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";

            if (utils.getGraphs()[i]->getName() == "shipping" || utils.getGraphs()[i]->getName() == "stadiums" || utils.getGraphs()[i]->getName() == "tourism") {
                string printEdges = "{";
                for (auto edge : tree) printEdges += "(" + to_string(edge.first) + ", " + to_string(edge.second) + "), ";
                printEdges += "\b\b}";
                cout << left << setw(125) << printEdges << '|' << endl;
            }
            else cout << left << setw(121) << ' ' << '|' << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n";
        press0ToContinue();

    }

    else if (command == "6") { // Christofides Heuristic

        cout << "   -CHOOSE A GRAPH: (ONLY COMPLETE GRAPHS)\n";
        for (int i = 1; i < utils.getGraphs().size() - 2; i++) {
            cout << "       [" << i << "]" << utils.getGraphs()[i]->getName() << '\n';
        }
        cout << "       [" << utils.getGraphs().size() - 2 << "] ALL\n";

        enterOption(utils.getGraphs().size() - 2);
        cout << endl;

        cout << "--------------------------------CHRISTOFIDES--------------------------------" << endl;
        cout << "|   GRAPH   |    RESULT   |  TIME  |                  PATH                 |" << endl;

        unsigned i;
        if (stoi(command) == utils.getGraphs().size() - 2) i = 1;
        else i = stoi(command);

        vector<pair<unsigned, string>> graphsToImprove;
        vector<pair<double, vector<unsigned>>> resultsToImprove;

        for (i; i < utils.getGraphs().size() - 2; (command == to_string(utils.getGraphs().size() - 2) ? i++ : i = utils.getGraphs().size() - 2)) {

            vector<unsigned> path;
            auto start = chrono::high_resolution_clock::now();
            double result = utils.getGraphs()[i]->christofides(path);
            auto end = chrono::high_resolution_clock::now();

            graphsToImprove.emplace_back(i, utils.getGraphs()[i]->getName());
            resultsToImprove.emplace_back(result, path);

            cout << "| " << left << setw(9) << utils.getGraphs()[i]->getName() << " | " << left << setw(11) << result << " | "
                 << left << setw(7) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << "| ";

            if (utils.getGraphs()[i]->getName() == "stadiums" || utils.getGraphs()[i]->getName() == "tourism") {
                string printPath = "{";
                for (auto node : path) {
                    printPath += to_string(node) + ", ";
                }
                printPath += "\b\b}";
                cout << left << setw(41) << printPath << " |" << endl;
            }
            else cout << left << setw(37) << " " << " |" << endl;
        }
        cout << "----------------------------------------------------------------------------" << "\n\n";

        while (true) {
            cout << "PRESS 0 TO CONTINUE OR 1 TO IMPROVE THE RESULTS: "; getline(cin >> ws, command);
            if (command == "0" || command == "1") break;
        }

        if (command == "1") {
            cout << endl;
            cout << "--------------CHRISTOFIDES 2 OPT IMPROVEMENT-------------" << endl;
            cout << "|   GRAPH   | CHRISTOFIDES | CHRISTOFIDES2OPT |   TIME  |" << endl;

            for (unsigned j = 0; j < graphsToImprove.size(); j++) {
                cout << "| " << left << setw(9) << graphsToImprove[j].second << " | " << left << setw(12) << resultsToImprove[j].first << " | ";
                auto start = chrono::high_resolution_clock::now();
                double improved = utils.getGraphs()[graphsToImprove[j].first]->tSP2OptImprovement(resultsToImprove[j].second);
                auto end = chrono::high_resolution_clock::now();
                cout << left << setw(16) << improved << " | " << left << setw(7) << to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " |" << endl;
            }
            cout << "---------------------------------------------------------" << "\n\n";
            press0ToContinue();
        }
    }

    else if (command == "7") { // Apply all algorithms to all graphs
            command = "5";
            cout << endl;
            return;
    }

    else {
            command = "0";
            return;
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
                cout << "   [" << next << ']' << ((graph->getName() == "tourism") ? nodes[next]->label : "") << " Distance: " << i->distance << endl;
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