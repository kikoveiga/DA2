//
// Created by kikoveiga on 29-04-2023.
//

#include <iostream>
#include <chrono>
#include <list>

#include "../headers/Menu.h"

using namespace std;

void testIsComplete(const vector<Graph*>& graphs) {

    cout << "-Testing IsComplete()-" << endl;
    cout << "|   GRAPH   | RESULT |" << endl;
    for (auto graph : graphs) {

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(7) << (graph->isComplete() ? "True" : "False") << '|' << endl;
    }
    cout << "----------------------" << "\n\n";
}

void testIsConnected(const vector<Graph*>& graphs) {

    cout << "-----Testing IsConnected()-----" << endl;
    cout << "|   GRAPH   | RESULT |  TIME  |" << endl;

    for (auto graph : graphs) {

        auto start = chrono::high_resolution_clock::now();
        bool result = graph->isConnected();
        auto end = chrono::high_resolution_clock::now();
        cout << "| " << left << setw(9) << graph->getName() << " |  " << left << setw(5) << (result ? "True" : "False") << " | "
        << left << setw(7) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << '|' << endl;
    }
    cout << "-------------------------------" << "\n\n";
}

void testTSPBacktracking(const vector<Graph*>& graphs) {

    cout << "-----------------------------Testing TSPBacktracking()----------------------------" << endl;
    cout << "|   GRAPH  | RESULT |  TIME  |                        PATH                       |" << endl;

    for (auto graph : graphs) {

        if (graph->getName() != "shipping" && graph->getName() != "stadiums" && graph->getName() != "tourism") continue;

        vector<unsigned> bestPath;

        auto start = chrono::high_resolution_clock::now();
        double result = graph->solveTSPWithBacktracking(bestPath);
        auto end = chrono::high_resolution_clock::now();

        cout << "| " << left << setw(8) << graph->getName() << " | " << left << setw(6) << result << " | "
        << left << setw(7) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << "| {";

        string printPath;
        for (auto node : bestPath) {
            printPath += to_string(node) + ", ";
        }
        printPath += "\b\b} ";

        cout << left << setw(53) << printPath << '|' << endl;
    }
    cout << "----------------------------------------------------------------------------------" << "\n\n";
}

void testTSPNNHeuristic(const vector<Graph*>& graphs) {

    cout << "--------------------------Testing TSPNNHeuristic()--------------------------" << endl;
    cout << "|   GRAPH   |    RESULT   |  TIME  |                  PATH                 |" << endl;

    for (auto graph : graphs) {

        if (graph->getName() == "shipping") continue;

        vector<unsigned> path;
        auto start = chrono::high_resolution_clock::now();
        double result = graph->tSPNNHeuristic(path);
        auto end = chrono::high_resolution_clock::now();

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(11) << result << " | "
        << left << setw(6) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";

        if (graph->getName() == "stadiums" || graph->getName() == "tourism") {
            string printPath = "{";
            for (auto node : path) {
                printPath += to_string(node) + ", ";
            }
            printPath += "\b\b}";

            cout << left << setw(42) << printPath << '|' << endl;
        }
        else cout << left << setw(38) << ' ' << '|' << endl;
    }
    cout << "----------------------------------------------------------------------------" << "\n\n";
}

void testTSPGreedyHeuristic(const vector<Graph*>& graphs) {

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

void testMSTPrim(const vector<Graph*>& graphs) {

    cout << "-------------------------------------------------------------------Testing MSTPrim()------------------------------------------------------------------" << endl;
    cout << "|   GRAPH   |    RESULT   |  TIME  |                                                       EDGES                                                     |" << endl;

    for (auto graph : graphs) {

        vector<pair<unsigned, unsigned>> mST;
        auto start = chrono::high_resolution_clock::now();
        double result = graph->mSTPrim(mST);
        auto end = chrono::high_resolution_clock::now();
        sort(mST.begin(), mST.end());

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(11) << result << " | "
        << left << setw(6) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";


        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            string printEdges = "{";
            for (auto edge : mST) {
                printEdges += "(" + to_string(edge.first) + ", " + to_string(edge.second) + "), ";
            }
            printEdges += "\b\b}";
            cout << left << setw(116) << printEdges << '|' << endl;
        }
        else cout << left << setw(112) << ' ' << '|' << endl;

    }
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n";
}

void testMSTKruskal(const vector<Graph*>& graphs) {

    cout << "------------------------------------------------------------------Testing MSTKruskal()------------------------------------------------------------------" << endl;
    cout << "|   GRAPH   |    RESULT   |   TIME   |                                                      EDGES                                                      |" << endl;

    for (auto graph : graphs) {

        vector<pair<unsigned, unsigned>> mST;

        auto start = chrono::high_resolution_clock::now();
        double result = graph->mSTKruskal(mST);
        auto end = chrono::high_resolution_clock::now();
        sort(mST.begin(), mST.end());

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(11) << result << " | "
        << left << setw(8) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";

        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            string printEdges = "{";
            for (auto edge : mST) {
                printEdges += "(" + to_string(edge.first) + ", " + to_string(edge.second) + "), ";
            }
            printEdges += "\b\b}";
            cout << left << setw(116) << printEdges << '|' << endl;
        }
        else cout << left << setw(112) << ' ' << '|' << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n";
}

void testTSP1TreeLowerBound(const vector<Graph*>& graphs) {

    cout << "-------------------------------------------------------------------Testing TSP1TreeLowerBound()------------------------------------------------------------------" << endl;

    for (auto graph : graphs) {

        vector<pair<unsigned, unsigned>> tree;

        auto start = chrono::high_resolution_clock::now();
        double result = graph->tSP1TreeLowerBound(tree);
        auto end = chrono::high_resolution_clock::now();
        sort(tree.begin(), tree.end());

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(11) << result << " | "
        << left << setw(8) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | ";

        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            string printEdges = "{";
            for (auto edge : tree) printEdges += "(" + to_string(edge.first) + ", " + to_string(edge.second) + "), ";
            printEdges += "\b\b}";
            cout << left << setw(125) << printEdges << '|' << endl;
        }
        else cout << left << setw(121) << ' ' << '|' << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n\n";
}

void testFindArticulationPoints(const vector<Graph*>& graphs) {

    cout << "-Testing findArticulationPoints()-" << endl;
    cout << "|   GRAPH   |  RESULT  |   TIME  |" << endl;

    for (auto graph : graphs) {

        auto start = chrono::high_resolution_clock::now();
        set<unsigned> articulationPoints = graph->findArticulationPoints();
        auto end = chrono::high_resolution_clock::now();

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(8) << articulationPoints.size() << " | "
        << left << setw(7) <<  to_string(chrono::duration_cast<chrono::milliseconds>(end - start).count()) + " ms" << " | " << endl;
    }
    cout << "----------------------------------" << "\n\n";
}

void testChristofides(const vector<Graph*>& graphs) {

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

void testTSP2Approximation(const vector<Graph*>& graphs) {

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

void testTSP2OptImprovement(const vector<Graph*>& graphs) {

    cout << "------------------------Testing TSP2OptImprovement()-----------------------" << endl;
    cout << "|   GRAPH   | CHRISTOFIDES | CHRISTOFIDES2OPT |      NN     |    NN2OPT   |" << endl;

    for (auto graph : graphs) {
        if (!graph->isComplete()) continue;

        vector<unsigned> path;
        double result1 = graph->christofides(path);
        double improved1 = graph->tSP2OptImprovement(path);

        double result2 = graph->tSPNNHeuristic(path);
        double improved2 = graph->tSP2OptImprovement(path);

        cout << "| " << left << setw(9) << graph->getName() << " | " << left << setw(12) << result1 << " | "
        << left << setw(16) << improved1 << " | " << left << setw(11) << result2 << " | " << left << setw(11) << improved2 << " |" << endl;
    }
    cout << "---------------------------------------------------------------------------" << "\n\n";
}

int main() {

    //Menu menu;

    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    testIsComplete(graphs);
    testIsConnected(graphs);
    testTSPBacktracking(graphs);
    testTSPNNHeuristic(graphs);
    testTSPGreedyHeuristic(graphs);
    testMSTPrim(graphs);
    testMSTKruskal(graphs);
    testTSP1TreeLowerBound(graphs);
    testFindArticulationPoints(graphs);
    testChristofides(graphs);
    testTSP2Approximation(graphs);
    testTSP2OptImprovement(graphs);
}