//
// Created by kikoveiga on 29-04-2023.
//

#include <iostream>
#include <chrono>
#include <list>

#include "../headers/Menu.h"

using namespace std;

void testIsComplete() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "---Testing IsComplete()---" << endl;
    for (auto graph : graphs) {

        cout << graph->getName() << ' ' << graph->isComplete() << endl;
    }
    cout << "--------------------------" << "\n\n";
}

void testIsConnected() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "---Testing IsConnected()---" << endl;

    for (auto graph : graphs) {

        auto start = chrono::high_resolution_clock::now();
        bool result = graph->isConnected();
        auto end = chrono::high_resolution_clock::now();
        cout << graph->getName() << ' ' << result << " Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
    cout << "---------------------------" << "\n\n";
}

void testTSPBacktracking() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "--------------------------------Testing TSPBacktracking()--------------------------------" << endl;

    for (auto graph : graphs) {
        if (!graph->isRealOrToy() && graph->getName()[0] != 'e') {

            vector<unsigned> bestPath;

            auto start = chrono::high_resolution_clock::now();
            double result = graph->solveTSPWithBacktracking(bestPath);
            auto end = chrono::high_resolution_clock::now();

            cout << graph->getName() << " Result: " << result << " Path: {";
            for (auto node : bestPath) {
                cout << node << ", ";
            }
            cout << "\b\b} Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
        }
    }
    cout << "-----------------------------------------------------------------------------------------" << "\n\n";
}

void testTSPNNHeuristic() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "----------------------------Testing TSPNNHeuristic()----------------------------" << endl;

    for (auto graph : graphs) {

        if (graph->getName() == "shipping") continue;

        vector<unsigned> path;
        auto start = chrono::high_resolution_clock::now();
        double result = graph->tSPNNHeuristic(path);
        auto end = chrono::high_resolution_clock::now();

        cout << graph->getName() << " Result: " << result;

        if (graph->getName() == "stadiums" || graph->getName() == "tourism") {
            cout << " Path: {";
            for (auto node : path) {
                cout << node << ", ";
            }
            cout << "\b\b}";
        }
        cout << " Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
    cout << "--------------------------------------------------------------------------------" << "\n\n";
}

void testMSTPrim() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "-----------------------------------------------------------------------Testing MSTPrim()-----------------------------------------------------------------------" << endl;

    for (auto graph : graphs) {

        cout << graph->getName() << " Result: ";

        vector<pair<unsigned, unsigned>> mST;
        auto start = chrono::high_resolution_clock::now();
        double result = graph->mSTPrim(mST);
        auto end = chrono::high_resolution_clock::now();
        cout << result << " || ";

        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            cout << "Edges: {";
            for (auto edge : mST) {
                cout << "(" << edge.first << ", " << edge.second << "), ";
            }
            cout << "\b\b} || ";
        }
        cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n";
}

void testMSTKruskal() {

    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "--------------------------------Testing MSTKruskal()--------------------------------" << endl;

    for (auto graph : graphs) {

        vector<pair<unsigned, unsigned>> mST;

        auto start = chrono::high_resolution_clock::now();
        double result = graph->mSTKruskal(mST);
        auto end = chrono::high_resolution_clock::now();
        cout << graph->getName() << " Result: " << result << " || ";

        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            cout << "Edges: {";
            for (auto edge : mST) {
                cout << "(" << edge.first << ", " << edge.second << "), ";
            }
            cout << "\b\b} || ";
        }
        cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
    cout << "----------------------------------------------------------------------------------" << "\n\n";
}

void testTSP1TreeLowerBound() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "--------------------------------Testing TSP1TreeLowerBound()--------------------------------" << endl;

    for (auto graph : graphs) {

        vector<pair<unsigned, unsigned>> tree;

        auto start = chrono::high_resolution_clock::now();
        double result = graph->tSP1TreeLowerBound(tree);
        auto end = chrono::high_resolution_clock::now();
        cout << graph->getName() << " Result: " << result;

        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            cout << " Edges: {";
            for (auto edge : tree) {
                cout << "(" << edge.first << ", " << edge.second << "), ";
            }
            cout << "\b\b} ||";
        }
        cout << " Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
    cout << "-------------------------------------------------------------------------------------------" << "\n\n";
}

void testFindArticulationPoints() {

    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "--------------------------------Testing findArticulationPoints()--------------------------------" << endl;

    for (auto graph : graphs) {

        if (graph->getName() != "stadiums") continue;

        auto start = chrono::high_resolution_clock::now();
        vector<unsigned> articulationPoints = graph->findArticulationPoints();
        auto end = chrono::high_resolution_clock::now();
        cout << graph->getName() << " Articulation Points: {";
        for (auto node : articulationPoints) {
            cout << node << ", ";
        }
        cout << "\b\b} Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
    cout << "------------------------------------------------------------------------------------------------" << "\n\n";
}

void testTSPGreedyHeuristic() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "------------------------Testing TSPGreedyHeuristic()------------------------" << endl;
    cout << "|   GRAPH   |    RESULT   |  TIME  |                  PATH                 |" << endl;

    for (auto graph : graphs) {

        if (!graph->isComplete()) continue;
        vector<pair<unsigned, unsigned>> path;

        auto start = chrono::high_resolution_clock::now();
        double result = graph->tSPGreedyHeuristic(path);
        auto end = chrono::high_resolution_clock::now();

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(11) << result << " | "
        << left << setw(6) << to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";

        if (graph->getName() == "stadiums" || graph->getName() == "tourism") {
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
    cout << "----------------------------------------------------------------------------" << "\n\n";
}

void testChristofides() {

    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    cout << "---------------------------Testing Christofides()---------------------------" << endl;
    cout << "|   GRAPH   |    RESULT   |  TIME  |                  PATH                 |" << endl;

    for (auto graph : graphs) {

        if (!graph->isComplete()) continue;
        vector<unsigned> path;

        auto start = chrono::high_resolution_clock::now();
        double result = graph->christofides(path);
        auto end = chrono::high_resolution_clock::now();

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(11) << result << " | "
        << left << setw(6) << to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";

        if (graph->getName() == "stadiums" || graph->getName() == "tourism") {
            string printPath = "{";
            for (auto node : path) {
                printPath += to_string(node) + ", ";
            }
            printPath += "\b\b}";
            cout << left << setw(41) << printPath << " |";
        }

        else cout << left << setw(37) << " " << " |";

        cout << endl;
    }
    cout << "----------------------------------------------------------------------------" << "\n\n";
}

void testTSP2Approximation() {

        Utils utils;
        vector<Graph*> graphs = utils.getGraphs();

        cout << "------------------------Testing TSP2Approximation()--------------------------" << endl;
        cout << "|   GRAPH   |    RESULT   |   TIME  |                  PATH                 |" << endl;

        for (auto graph : graphs) {

            if (graph->getName() == "shipping") continue;
            vector<unsigned> path;

            auto start = chrono::high_resolution_clock::now();
            double result = graph->tSP2Approximation(path);
            auto end = chrono::high_resolution_clock::now();

            cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(11) << result << " | "
            << left << setw(7) << to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";

            if (graph->getName() == "stadiums" || graph->getName() == "tourism") {
                string printPath = "{";
                for (auto node : path) {
                    printPath += to_string(node) + ", ";
                }
                printPath += "\b\b}";
                cout << left << setw(41) << printPath << " |";
            }

            else cout << left << setw(37) << " " << " |";

            cout << endl;
        }
        cout << "-----------------------------------------------------------------------------" << "\n\n";
}

int main() {

    //Menu menu;

    //testIsComplete();
    //testIsConnected();
    //testTSPBacktracking();
    //testTSPNNHeuristic();
    //testMSTPrim();
    //testMSTKruskal();
    //testTSP1TreeLowerBound();
    //testFindArticulationPoints();
    //testTSPGreedyHeuristic();
    //testChristofides();
    testTSP2Approximation();
}
