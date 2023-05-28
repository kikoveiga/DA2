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

Graph::Edge* Graph::findEdge(int first, int second) {

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

unsigned Graph::getNumberOfEdges() const {

    unsigned numberOfEdges = 0;

    for (auto node : nodes) {
        numberOfEdges += node->adj.size();
    }

    return numberOfEdges / 2;
}

float Graph::calculateCost(const vector<int>& tour) {
    float cost = 0;

    for (int i = 0; i < nodes.size() - 1; i++) {

        cost += findEdge(tour[i], tour[i + 1])->distance;
    }

    Edge* edge = findEdge(tour.back(), tour.front());
    cost += edge == nullptr ? 0 : edge->distance;

    return cost;
}

void Graph::tspBacktracking(unsigned current, vector<int>& currPath, float& minCost, unsigned depth, vector<int>& bestPath) {

    // Base case: all nodes visited
    if (depth == nodes.size()) {
        // Check if it forms a better tour
        float cost = calculateCost(currPath);
        if (cost < minCost) {
            minCost = cost;
            bestPath = currPath;
        }
        return;
    }

    // Try all possible next nodes
    for (auto i : nodes[current]->adj) {
        int next = i->first->id == current ? i->second->id : i->first->id;

        // If the next node hasn't been visited
        if (!nodes[next]->visited) {
            nodes[next]->visited = true;
            currPath.push_back(next);

            // Recursively check next nodes
            tspBacktracking(next, currPath, minCost, depth + 1, bestPath);


            // If it doesn't find a better cost tour, backtrack
            nodes[next]->visited = false;
            currPath.pop_back();
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
    vector<int> currPath;
    currPath.push_back(0);

    // Initialize the minimum cost to a large value
    float minCost = numeric_limits<float>::max();

    // Call the backtracking function
    vector<int> bestPath;
    tspBacktracking(0, currPath, minCost, 1, bestPath);

    for (int i : bestPath) {
        cout << i << ' ';
    }

    return minCost;
}


