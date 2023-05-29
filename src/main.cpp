//
// Created by kikoveiga on 29-04-2023.
//

#include <iostream>
#include <chrono>

#include "../headers/Menu.h"

using namespace std;

void testBacktracking() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    for (auto graph : graphs) {
        if (!graph->isRealOrToy() && graph->getName()[0] != 'e') {
            auto start = chrono::high_resolution_clock::now();
            cout << graph->getName() << ' ' << graph->solveTspWithBacktracking() << ' ';
            auto end = chrono::high_resolution_clock::now();
            cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
        }
    }
}

int main() {
    testBacktracking();
    //Menu menu;
}

