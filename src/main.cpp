//
// Created by kikoveiga on 29-04-2023.
//

#include <iostream>

#include "../headers/Utils.h"

using namespace std;

int main() {

    Utils utils;
    auto graph = utils.buildRealWorldGraph(1);

    cout << '{';
    for (auto node : graph->getNodes()) {
        cout << node->id << ", ";
    }
    cout << "\b\b}" << endl;

    for (auto node : graph->getNodes()) {
        cout << node->id << ": {";
        for (auto edge : node->adj) {
            node == edge->first ? cout << edge->second->id << ", " : cout << edge->first->id << ", ";
        }
        cout << "\b\b}" << endl;
    }
}

