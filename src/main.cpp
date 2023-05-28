//
// Created by kikoveiga on 29-04-2023.
//

#include <iostream>

#include "../headers/Menu.h"

using namespace std;

void testBacktracking() {
    Utils utils;
    vector<Graph*> graphs = utils.getGraphs();
    Graph* shipping_graph = graphs[3];
    Graph* stadiums_graph = graphs[4];
    Graph* tourism_graph = graphs[5];

    std::cout << shipping_graph->getName() << endl;
    float result = shipping_graph->solveTspWithBacktracking();
    std::cout << result << endl;

    std::cout << stadiums_graph->getName() << endl;
    float result2 = stadiums_graph->solveTspWithBacktracking();
    std::cout << result2 << endl;

    std::cout << tourism_graph->getName() << endl;
    float result3 = tourism_graph->solveTspWithBacktracking();
    std::cout << result3 << endl;
}

int main() {
    testBacktracking();
    //Menu menu;
}

