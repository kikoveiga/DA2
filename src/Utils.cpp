//
// Created by kikoveiga on 29-04-2023.
//

#include "../headers/Utils.h"

using namespace std;

Utils::Utils() {
    return;
}

void Utils::buildGraphs() {

    for (int i = 1; i <= 3; i++) {
        buildRealWorldGraph(i);
    }

    buildToyGraph("shipping.csv");
    buildToyGraph("stadiums.csv");
    buildToyGraph("tourism.csv");
}

Graph* Utils::buildRealWorldGraph(int number) {

    auto graph = new Graph("graph" + to_string(number), true);
    graphs.push_back(graph);

    buildRealWorldGraphNodes(number);
    buildRealWorldGraphEdges(number);

    return graph;
}

void Utils::buildRealWorldGraphNodes(int number) {

    ifstream file("../dataset/Real-World-Graphs/graph" + to_string(number) + "/nodes.csv");
    string line;
    getline(file, line);

    while (getline(file, line)) {

        string id, latitude, longitude;
        stringstream input(line);
        getline(input, id, ',');
        getline(input, longitude, ',');
        getline(input, latitude, '\r');

        graphs.back()->addNode(stoi(id), stof(latitude), stof(longitude));
    }
}

void Utils::buildRealWorldGraphEdges(int number) {

    ifstream file("../dataset/Real-World-Graphs/graph" + to_string(number) + "/edges.csv");
    string line;
    getline(file, line);

    while (getline(file, line)) {

        string first, second, distance;
        stringstream input(line);
        getline(input, first, ',');
        getline(input, second, ',');
        getline(input, distance, '\r');

        graphs.back()->addEdge(stoi(first), stoi(second), stof(distance));
    }
}

Graph* Utils::buildToyGraph(const string& filename) {

    ifstream file("../dataset/Toy-Graphs/" + filename);
    string line, last;
    getline(file, line);

    auto graph = new Graph(filename, false);
    graphs.push_back(graph);

    while (getline(file, line)) {

        string first, second, distance, labelFirst, labelSecond;
        stringstream input(line);
        getline(input, first, ',');
        getline(input, second, ',');
        getline(input, distance, filename == "tourism.csv" ? ',' : '\r');

        if (filename == "tourism.csv") {
            getline(input, labelFirst, ',');
            getline(input, labelSecond, '\r');
            graph->addNode(stoi(first), 0, 0, labelFirst);
            graph->addNode(stoi(second), 0, 0, labelSecond);
        }

        else {
            graph->addNode(stoi(first));
            graph->addNode(stoi(second));
        }

        graph->addEdge(stoi(first), stoi(second), stof(distance));
    }

    return graph;
}

vector<Graph*> Utils::getGraphs() {
    return graphs;
}


