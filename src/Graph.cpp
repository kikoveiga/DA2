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

float Graph::calculateCost(const std::vector<int>& tour) {
    float cost = 0;
    std::size_t number_of_nodes = nodes.size();

    for (int i = 0; i < number_of_nodes - 1; i++) {
        int current = tour[i];
        int next = tour[i+1];
        // Not sure if this is correct.
        // It should add the weight of the edge to the cost.
        cost += nodes[current]->adj[next]->distance;
    }

    // Add the cost of returning to the starting node (from the last node).
    // Not sure if this is needed!!
    int last_node = tour[number_of_nodes - 1];
    int first_node = tour[0];
    cost += nodes[last_node]->adj[first_node]->distance;

    return cost;
}

void Graph::tspBacktracking(int current, std::vector<int>& tour, float& minCost, int depth) {
    std::size_t number_of_nodes = nodes.size();

    // Base case: all nodes visited
    if (depth == number_of_nodes) {
        // Check if it forms a better tour
        float cost = calculateCost(tour);
        if (cost < minCost) {
            minCost = cost;
        }
        return;
    }

    // Try all possible next nodes
    for (int next = 0; next < number_of_nodes; next++) {
        if (!nodes[next]->visited) {
            nodes[next]->visited = true;
            tour.push_back(next);

            // Recursively check next nodes
            tspBacktracking(next, tour, minCost, depth + 1);

            // If it doesn't find a better cost tour, backtrack
            nodes[next]->visited = false;
            tour.pop_back();
        }
    }
}

void Graph::setAllNodesUnvisited() {
    for (auto& node : nodes) {
        node->visited = false;
    }
}

float Graph::solveTspWithBacktracking() {
    std::cout << 'a';

    // Set all nodes to unvisited
    setAllNodesUnvisited();

    // Start at the initial node (labeled with the zero-identifier label)
    nodes[0]->visited = true;

    // Create a tour vector to store the path
    std::vector<int> tour;
    tour.push_back(0);

    // Initialize the minimum cost to a large value
    float minCost = 99999999999.0; // hardcoded

    std::cout << 'a';

    // Call the backtracking function
    tspBacktracking(0, tour, minCost, 1);

    for (int i : tour) {
        std::cout << i << ' ';
    }

    return minCost;
}


