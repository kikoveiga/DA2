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

void Graph::addNode(unsigned id, double latitude, double longitude, const string& label) {

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

void Graph::addEdge(unsigned first, unsigned second, double distance) {
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

    return all_of(nodes.begin(), nodes.end(), [this](Node* node) { return node->adj.size() == nodes.size() - 1; });
}

bool Graph::isConnected() {

        setAllNodesUnvisited();
        dfs(0);

        return all_of(nodes.begin(), nodes.end(), [](Node* node) { return node->visited; });
}

void Graph::dfs(unsigned int node) {

    nodes[node]->visited = true;

    for (auto edge : nodes[node]->adj) {
        unsigned next = edge->first->id == node ? edge->second->id : edge->first->id;
        if (!nodes[next]->visited) {
            dfs(next);
        }
    }
}

unsigned Graph::getNumberOfEdges() const {

    unsigned numberOfEdges = 0;

    for (auto node : nodes) {
        numberOfEdges += node->adj.size();
    }

    return numberOfEdges / 2;
}

double Graph::haversine(Graph::Node* first, Graph::Node* second) {

        double lat1 = first->latitude;
        double lon1 = first->longitude;
        double lat2 = second->latitude;
        double lon2 = second->longitude;
        int R = 6371;

        double dLat = (lat2 - lat1)*M_PI/180.0;
        double dLon = (lon2 - lon1)*M_PI/180.0;

        lat1 = lat1*M_PI/180.0;
        lat2 = lat2*M_PI/180.0;

        double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2)*cos(lat1)*cos(lat2);
        double c = 2*asin(sqrt(a));

        return R*c;
}

void Graph::tspBacktracking(unsigned currNode, vector<unsigned>& currPath, double currDistance, double& minDistance, unsigned depth, vector<unsigned>& bestPath) {

    // Base case: all nodes visited
    if (depth == nodes.size()) {
        // Check if it forms a better tour
        Edge* edge = findEdge(0, currNode);
        edge != nullptr ? currDistance += edge->distance : currDistance = numeric_limits<double>::max();
        if (currDistance < minDistance) {
            minDistance = currDistance;
            bestPath = currPath;
            bestPath.push_back(0);
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

void Graph::setAllKeysToInfinity() {
    for (auto node : nodes) {
        node->key = numeric_limits<double>::max();
    }
}

double Graph::solveTspWithBacktracking(vector<unsigned>& path, vector<unsigned>& bestPath) {

    setAllNodesUnvisited();
    nodes[0]->visited = true;
    path.push_back(0);
    double minCost = numeric_limits<double>::max();

    tspBacktracking(0, path, 0, minCost, 1, bestPath);
    return minCost;
}

double Graph::tspNNHeuristic(std::vector<unsigned>& path) {

    setAllNodesUnvisited();
    path.push_back(0);
    nodes[0]->visited = true;
    double distance = 0;

    while (path.size() != nodes.size()) {

        bool found = false; // For incomplete graphs where the algorithm can't find anymore adjacent nodes
        unsigned nextNode;
        double minDistance = numeric_limits<double>::max();

        for (auto edge : nodes[path.back()]->adj) {

            unsigned next = edge->first->id == path.back() ? edge->second->id : edge->first->id;

            if (!nodes[next]->visited && edge->distance < minDistance) {
                nextNode = next;
                minDistance = edge->distance;
                found = true;
            }
        }

        if (!found) {

            for (auto node : nodes) {

                if (!node->visited) {
                    double dist = haversine(node, nodes[path.back()]) < minDistance;
                    if (dist < minDistance) {
                        nextNode = node->id;
                        minDistance = dist;
                    }
                }
            }
        }

        path.push_back(nextNode);
        nodes[nextNode]->visited = true;
        distance += minDistance;
    }

    Edge* edge = findEdge(0, path.back());
    edge != nullptr ? distance += edge->distance : distance += haversine(nodes[0], nodes[path.back()]);

    setAllNodesUnvisited();
    return distance;
}

double Graph::mSTPrim(std::vector<std::pair<unsigned, unsigned>>& mstEdges) {

    typedef pair<double, unsigned> pairWeightNode;
    priority_queue<pairWeightNode, vector<pairWeightNode>, greater<>> pq;

    nodes[0]->key = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {

        unsigned node = pq.top().second;
        pq.pop();

        if (nodes[node]->visited) continue;

        nodes[node]->visited = true;

        for (auto edge : nodes[node]->adj) {

            unsigned next = edge->first->id == node ? edge->second->id : edge->first->id;

            if (!nodes[next]->visited && edge->distance < nodes[next]->key) {
                nodes[next]->key = edge->distance;
                nodes[next]->parentNode = (int)node;
                pq.emplace(edge->distance, next);
            }
        }
    }

    double result = 0;

    for (auto node : nodes) {
        if (node->parentNode != -1) {
            mstEdges.emplace_back(node->id < node->parentNode ? node->id : node->parentNode, node->id < node->parentNode ? node->parentNode : node->id);
            result += node->key;
        }
    }

    sort(mstEdges.begin(), mstEdges.end());

    for (auto node : nodes) {
        node->visited = false;
        node->key = numeric_limits<double>::infinity();
        node->parentNode = -1;
    }

    return result;
}

auto compareEdges = [](auto a, auto b) {return a->distance <= b->distance;};

unsigned Graph::findParentKruskal(unsigned parent[], unsigned component) {

    if (parent[component] == component) return component;

    return parent[component] = findParentKruskal(parent, parent[component]);
}

void Graph::unionSetKruskal(unsigned node1, unsigned node2, unsigned parent[], unsigned rank[]) {

    node1 = findParentKruskal(parent, node1);
    node2 = findParentKruskal(parent, node2);

    if (rank[node1] < rank[node2]) {
        parent[node1] = node2;
    }

    else if (rank[node1] > rank[node2]) {
        parent[node2] = node1;
    }

    else {
        parent[node2] = node1;
        rank[node1]++;
    }
}

double Graph::mSTKruskal(std::vector<std::pair<unsigned, unsigned>>& mstEdges) {

    double distance = 0;

    set<Edge*, decltype(compareEdges)> edges(compareEdges);

    for (auto node : nodes) {

        for (auto edge : node->adj) {
            edges.insert(edge);
        }
    }

    auto* parent = new unsigned[edges.size()];
    auto* rank = new unsigned[edges.size()];

    for (unsigned i = 0; i < edges.size(); i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (auto edge : edges) {

        unsigned node1 = edge->first->id;
        unsigned node2 = edge->second->id;

        if (findParentKruskal(parent, node1) != findParentKruskal(parent, node2)) {
            mstEdges.emplace_back(node1 < node2 ? node1 : node2, node1 < node2 ? node2 : node1);
            unionSetKruskal(node1, node2, parent, rank);
            distance += edge->distance;
        }
    }

    sort(mstEdges.begin(), mstEdges.end());
    return distance;
}


