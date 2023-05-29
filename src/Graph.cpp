//
// Created by kikoveiga on 29-04-2023.
//

#include "../headers/Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(const string& name, bool realOrToy) {
    this->name = name;
    this->realOrToy = realOrToy;
}

void Graph::addNode(unsigned id, float latitude, float longitude, const string& label) {

    if (latitude != 0) {
        auto node = new Node{id, {}, latitude, longitude};
        nodes.push_back(node);
        return;
    }

    if (nodes.size() > id) return;

    while (nodes.size() <= id) {
        auto node = new Node{.id = (unsigned)nodes.size(), .label = label};
        nodes.push_back(node);
    }
}

void Graph::addEdge(unsigned first, unsigned second, float distance) {
    auto edge = new Edge{nodes[first], nodes[second], distance};
    nodes[first]->adj.push_back(edge);
    nodes[second]->adj.push_back(edge);
}

Graph::Edge* Graph::findEdge(unsigned first, unsigned second) {

        for (auto edge : nodes[first]->adj) {
            if (edge->first->id == second || edge->second->id == second) {
                return edge;
            }
        }
        return nullptr;
}

const vector<Graph::Node*>& Graph::getNodes() const {
    return nodes;
}

const string& Graph::getName() const {
    return name;
}

bool Graph::isRealOrToy() const {
    return realOrToy;
}

bool Graph::isComplete() const {

    all_of(nodes.begin(), nodes.end(), [this](Node* node) { return node->adj.size() == nodes.size() - 1; });
}

unsigned Graph::getNumberOfEdges() const {

    unsigned numberOfEdges = 0;

    for (auto node : nodes) {
        numberOfEdges += node->adj.size();
    }

    return numberOfEdges / 2;
}

void Graph::tspBacktracking(unsigned currNode, vector<unsigned>& currPath, float currDistance, float& minDistance, unsigned depth, vector<unsigned>& bestPath) {

    // Base case: all nodes visited
    if (depth == nodes.size()) {
        // Check if it forms a better tour
        Edge* edge = findEdge(0, currNode);
        edge != nullptr ? currDistance += edge->distance : currDistance = numeric_limits<float>::max();
        if (currDistance < minDistance) {
            minDistance = currDistance;
            bestPath = currPath;
        }
        return;
    }

    // Try all possible next nodes
    for (auto i : nodes[currNode]->adj) {
        unsigned next = i->first->id == currNode ? i->second->id : i->first->id;

        // If the next node hasn't been visited
        if (!nodes[next]->visited && currDistance + i->distance < minDistance) {

            nodes[next]->visited = true;
            currPath.push_back(next);
            currDistance += i->distance;

            // Recursively check next nodes
            tspBacktracking(next, currPath, currDistance, minDistance, depth + 1, bestPath);

            // If it doesn't find a better cost tour, backtrack
            nodes[next]->visited = false;
            currPath.pop_back();
            currDistance -= i->distance;
        }
    }
}

void Graph::setAllNodesUnvisited() {
    for (auto node : nodes) {
        node->visited = false;
    }
}

float Graph::solveTspWithBacktracking() {

    // Set all nodes to unvisited
    setAllNodesUnvisited();

    // Start at the initial node (labeled with the zero-identifier label)
    nodes[0]->visited = true;

    // Create a tour vector to store the path
    vector<unsigned> currPath;
    currPath.push_back(0);

    // Initialize the minimum cost to a large value
    float minCost = numeric_limits<float>::max();

    // Call the backtracking function
    vector<unsigned> bestPath;
    tspBacktracking(0, currPath, 0, minCost, 1, bestPath);

    for (auto i : bestPath) {
        cout << i << ' ';
    }

    return minCost;
}


