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

    for (auto graph : graphs) {
        cout << graph->getName() << ' ' << graph->isComplete() << endl;
    }
}

void testIsConnected() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    for (auto graph : graphs) {
        cout << graph->getName() << ' ' << graph->isConnected() << endl;
    }
}

void testTspBacktracking() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    for (auto graph : graphs) {
        if (!graph->isRealOrToy() && graph->getName()[0] != 'e') {
            vector<unsigned> path;
            vector<unsigned> bestPath;


            auto start = chrono::high_resolution_clock::now();
            double result = graph->solveTspWithBacktracking(path, bestPath);
            auto end = chrono::high_resolution_clock::now();

            cout << graph->getName() << " Result: " << result << " Path: {";
            for (auto node : bestPath) {
                cout << node << ", ";
            }
            cout << "\b\b} Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
        }
    }
}

void testTspNNHeuristic() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    for (auto graph : graphs) {
        vector<unsigned> path;
        auto start = chrono::high_resolution_clock::now();
        double result = graph->tspNNHeuristic(path);
        auto end = chrono::high_resolution_clock::now();

        cout << graph->getName() << " Result: " << result << " Time: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
}

void testMSTPrim() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    for (auto graph : graphs) {

        vector<pair<unsigned, unsigned>> mstEdges;

        cout << graph->getName() << " Result: ";

        auto start = chrono::high_resolution_clock::now();
        double result = graph->mSTPrim(mstEdges);
        auto end = chrono::high_resolution_clock::now();
        cout << result << " || ";

        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            cout << "Edges: {";
            for (auto edge : mstEdges) {
                cout << "(" << edge.first << ", " << edge.second << "), ";
            }
            cout << "\b\b} || ";
        }
        cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
}

void testMSTKruskal() {

    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    for (auto graph : graphs) {

        vector<pair<unsigned, unsigned>> mstEdges;

        cout << graph->getName() << " Result: ";

        auto start = chrono::high_resolution_clock::now();
        double result = graph->mSTKruskal(mstEdges);
        auto end = chrono::high_resolution_clock::now();
        cout << result << " || ";

        if (graph->getName() == "shipping" || graph->getName() == "stadiums" || graph->getName() == "tourism") {
            cout << "Edges: {";
            for (auto edge : mstEdges) {
                cout << "(" << edge.first << ", " << edge.second << "), ";
            }
            cout << "\b\b} || ";
        }
        cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    }
}

int main() {

    //Menu menu;

    //testIsComplete();
    //testIsConnected();
    //testTspBacktracking();
    //testTspNNHeuristic();
    testMSTPrim();
    //testMSTKruskal();
}

