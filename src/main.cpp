//
// Created by kikoveiga on 29-04-2023.
//

#include <iostream>

#include "../headers/Menu.h"
#include "../headers/Utils.h"

using namespace std;

void testBacktracking() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();

    for (Graph* graph : graphs) {
        std::cout << graph->getName() << endl;
    }

    Graph* shipping_graph = graphs[3];

    float result = shipping_graph->solveTspWithBacktracking();
    std::cout << result;
}

int main() {
    testBacktracking();
    // Menu menu;
}

