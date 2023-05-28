//
// Created by kikoveiga on 29-04-2023.
//

#include <iostream>

#include "../headers/Menu.h"

using namespace std;

void testBacktracking() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();
    Graph* shipping_graph = graphs[0];

    float result = shipping_graph->solveTspWithBacktracking();
    std::cout << result;
}

int main() {
    testBacktracking();
    //Menu menu;
}

