//
// Created by kikoveiga on 29-04-2023.
//

#include "../headers/Graph.h"

using namespace std;

Graph::Graph(const string& name, bool realOrToy) {
    this->name = name;
    this->realOrToy = realOrToy;
}

void Graph::addNode(int id, float latitude, float longitude, const string& label) {

    if (latitude != 0) {
        auto node = new Node{id, {}, latitude, longitude};
        nodes.push_back(node);
        return;
    }

    if (nodes.size() > id) return;

    while (nodes.size() <= id) {
        auto node = new Node{.id = (int)nodes.size(), .label = label};
        nodes.push_back(node);
    }
}

void Graph::addEdge(int first, int second, float distance) {
    auto edge = new Edge{nodes[first], nodes[second], distance};
    nodes[first]->adj.push_back(edge);
    nodes[second]->adj.push_back(edge);
}

vector<Graph::Node*> Graph::getNodes() const {
    return nodes;
}
