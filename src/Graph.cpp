//
// Created by kikoveiga on 29-04-2023.
//

#include "../headers/Graph.h"

using namespace std;

auto compareEdges = [](auto a, auto b) {return a != b && a->distance >= b->distance;};

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

    return all_of(nodes.begin(), nodes.end(), [this](Node* node) {return node->adj.size() == nodes.size() - 1;});
}

bool Graph::isConnected() {

        dfs(0);

        bool isConnected = all_of(nodes.begin(), nodes.end(), [](Node* node) {return node->visited;});
        setAllNodesUnvisited();
        return isConnected;
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

void Graph::dfs(unsigned node) {

    nodes[node]->visited = true;

    for (auto edge : nodes[node]->adj) {
        unsigned next = edge->first->id == node ? edge->second->id : edge->first->id;
        if (!nodes[next]->visited) {
            dfs(next);
        }
    }
}

void Graph::dfsTree(unsigned node, vector<unsigned>& tree) {

    nodes[node]->visited = true;
    tree.push_back(node);

    for (auto edge : nodes[node]->adj) {
        unsigned next = edge->first->id == node ? edge->second->id : edge->first->id;
        if (!nodes[next]->visited) {
            dfsTree(next, tree);
            tree.push_back(node);
        }
    }
}

void Graph::dfsArticulationPoints(unsigned int node, int num[], int low[],  unsigned& counter, std::set<unsigned int>& articulationPoints) {

    nodes[node]->visited = true;
    num[node] = low[node] = (int)counter++;

    for (auto edge : nodes[node]->adj) {
        unsigned next = edge->first->id == node ? edge->second->id : edge->first->id;

        if (num[next] == -1) {

            nodes[next]->parent = nodes[node];
            dfsArticulationPoints(next, num, low, counter, articulationPoints);
            low[node] = min(low[node], low[next]);

            if (node != 0 && low[next] >= num[node]) {
                articulationPoints.insert(node);
            }

        }
        else if (nodes[next]->visited) low[node] = min(low[node], num[next]);
    }
    nodes[node]->visited = false;
}

unsigned Graph::getNumberOfEdges() const {

    unsigned numberOfEdges = 0;
    for (auto node : nodes) {
        numberOfEdges += node->adj.size();
    }

    return numberOfEdges / 2;
}

set<unsigned> Graph::findArticulationPoints() {

    set<unsigned> articulationPoints;
    if (isComplete()) return articulationPoints;

    unsigned counter = 0;
    stack<unsigned> stack;
    auto* num = new int[nodes.size()];
    auto* low = new int[nodes.size()];

    for (unsigned i = 0; i < nodes.size(); i++) {
        num[i] = -1;
        low[i] = -1;
    }

    for (auto node : nodes) {
        if (!node->visited) {
            dfsArticulationPoints(node->id, num, low, counter, articulationPoints);
        }
    }

    // Check if node 0 is an articulation point
    int children = 0;
    for (auto edge : nodes[0]->adj) {
        unsigned next = edge->second->id;
        if (nodes[next]->parent == nodes[0]) {
            children++;
        }

        if (children > 1) {
            articulationPoints.insert(0);
            break;
        }
    }

    for (auto node : nodes) {
        node->parent = nullptr;
    }

    return articulationPoints;
}

void Graph::tSPBacktracking(unsigned currNode, vector<unsigned>& currPath, double currDistance, double& minDistance, vector<unsigned>& bestPath) {

    // Base case: all nodes visited
    if (currPath.size() == nodes.size()) {
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
            tSPBacktracking(next, currPath, currDistance, minDistance, bestPath);

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

void Graph::setAllDegreesTo0() {
    for (auto node : nodes) {
        node->degree = 0;
    }
}

double Graph::solveTSPWithBacktracking(vector<unsigned>& bestPath) {

    nodes[0]->visited = true;
    vector<unsigned> path;
    path.push_back(0);
    double minCost = numeric_limits<double>::max();

    tSPBacktracking(0, path, 0, minCost, bestPath);
    setAllNodesUnvisited();
    return minCost;
}

double Graph::tSPNNHeuristic(std::vector<unsigned>& path) {

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
    path.push_back(0);

    setAllNodesUnvisited();
    return distance;
}

double Graph::tSPGreedyHeuristic(vector<pair<unsigned, unsigned>>& path) {

    path.clear();

    double distance = 0;
    priority_queue<Edge*, vector<Edge*>, decltype(compareEdges)> edges(compareEdges);

    for (auto node : nodes) {
        for (auto edge : node->adj) {

            if (!edge->visited) {
                edges.push(edge);
                edge->visited = true;
            }
        }
    }

    auto* parent = new unsigned[edges.size()];
    auto* rank = new unsigned[edges.size()];

    for (unsigned i = 0; i < edges.size(); i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    while (path.size() != nodes.size()) {

        Edge* edge = edges.top();
        edge->visited = false;
        edges.pop();

        if (edge->first->degree < 2 && edge->second->degree < 2
        && (path.size() == nodes.size() - 1 || findParentKruskal(parent, edge->first->id) != findParentKruskal(parent, edge->second->id))) {

            path.emplace_back(edge->first->id, edge->second->id);

            edge->first->degree++;
            edge->second->degree++;
            distance += edge->distance;
            unionSetKruskal(edge->first->id, edge->second->id, parent, rank);
        }
    }

    for (auto node : nodes) {
        node->degree = 0;
    }

    while (!edges.empty()) {
        edges.top()->visited = false;
        edges.pop();
    }

    return distance;
}

double Graph::mSTPrim(vector<pair<unsigned, unsigned>>& mST) {

    mST.clear();
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
                nodes[next]->parent = nodes[node];
                pq.emplace(edge->distance, next);
            }
        }
    }

    double result = 0;

    for (auto node : nodes) {
        if (node->parent != nullptr) {
            mST.emplace_back(node->id < node->parent->id ? node->id : node->parent->id,
                             node->id > node->parent->id ? node->id : node->parent->id);
            result += node->key;
            node->degree++;
            node->parent->degree++;
        }
    }

    for (auto node : nodes) {
        node->visited = false;
        node->key = numeric_limits<double>::infinity();
        node->parent = nullptr;
    }

    return result;
}

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

double Graph::mSTKruskal(std::vector<std::pair<unsigned, unsigned>>& mST) {

    mST.clear();

    priority_queue<Edge*, vector<Edge*>, decltype(compareEdges)> edges(compareEdges);

    for (auto node : nodes) {
        for (auto edge : node->adj) {

            if (!edge->visited) {
                edges.push(edge);
                edge->visited = true;
            }
        }
    }

    auto* parent = new unsigned[edges.size()];
    auto* rank = new unsigned[edges.size()];

    for (unsigned i = 0; i < edges.size(); i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    double distance = 0;

    while (mST.size() != nodes.size() - 1) {

        Edge* edge = edges.top();
        edge->visited = false;
        edges.pop();

        unsigned node1 = edge->first->id;
        unsigned node2 = edge->second->id;

        if (findParentKruskal(parent, node1) != findParentKruskal(parent, node2)) {
            mST.emplace_back(node1, node2);
            unionSetKruskal(node1, node2, parent, rank);
            distance += edge->distance;
        }
    }

    while (!edges.empty()) {
        edges.top()->visited = false;
        edges.pop();
    }

    return distance;
}

double Graph::tSP2Approximation(std::vector<unsigned>& path) {

    path.clear();
    vector<pair<unsigned, unsigned>> mST;
    mSTPrim(mST);

    Graph mSTGraph("mSTGraph", realOrToy);

    for (auto node : nodes) {
        mSTGraph.addNode(node->id);
    }

    for (auto edge : mST) {
        mSTGraph.addEdge(edge.first, edge.second, findEdge(edge.first, edge.second)->distance);
    }

    vector<unsigned> tree;
    mSTGraph.dfsTree(0, tree);
    path.push_back(0);
    double distance = 0;
    unsigned last = 0;

    for (unsigned i = 1; i < tree.size() - 1; i++) {
        if (find(path.begin(), path.end(), tree[i]) == path.end()) {
            path.push_back(tree[i]);
            auto edge = findEdge(last, tree[i]);
            edge == nullptr ? distance += haversine(nodes[last], nodes[tree[i]]) : distance += edge->distance;
            last = tree[i];
        }
    }
    path.push_back(0);
    auto edge = findEdge(last, 0);
    edge == nullptr ? distance += haversine(nodes[0], nodes[last]) : distance += edge->distance;

    return distance;
}

double Graph::tSP1TreeLowerBound(std::vector<pair<unsigned, unsigned>>& tree) {

    double bestLowerBound = 0;
    set<unsigned> articulationPoints = findArticulationPoints();

    for (auto node : nodes) {

        if (articulationPoints.find(node->id) != articulationPoints.end()) continue;

        node->visited = true;
        vector<pair<unsigned, unsigned>> mST;
        double lowerBound = mSTPrim(mST);

        auto* shortestEdge = new Edge{nullptr, nullptr, numeric_limits<double>::max()};
        auto* secondShortestEdge = new Edge{nullptr, nullptr, numeric_limits<double>::max()};

        for (auto edge : node->adj) {
            if (edge->distance < shortestEdge->distance) {
                secondShortestEdge = shortestEdge;
                shortestEdge = edge;
            }
            else if (edge->distance < secondShortestEdge->distance) {
                secondShortestEdge = edge;
            }
        }

        lowerBound += shortestEdge->distance + secondShortestEdge->distance;

        if (lowerBound > bestLowerBound) {
            bestLowerBound = lowerBound;
            tree = mST;
            tree.emplace_back(shortestEdge->first->id, shortestEdge->second->id);
            tree.emplace_back(secondShortestEdge->first->id, secondShortestEdge->second->id);
        }
    }

    setAllNodesUnvisited();
    return bestLowerBound;
}

void Graph::eulerianCircuitHierholzer(vector<unsigned>& eulerianCircuit) {

    vector<unsigned> currCircuit;
    currCircuit.push_back(0);

    while (eulerianCircuit.size() != getNumberOfEdges() + 1) {

        unsigned currNode = currCircuit.back();
        bool found = false;

        for (auto edge : nodes[currNode]->adj) {

            if (!edge->visited) {
                edge->visited = true;
                found = true;

                unsigned next = edge->first->id == currNode ? edge->second->id : edge->first->id;
                currCircuit.push_back(next);

                break;
            }
        }

        if (found) continue;

        if (eulerianCircuit.empty()) eulerianCircuit = currCircuit;

        else eulerianCircuit.insert(find(eulerianCircuit.begin(), eulerianCircuit.end(), *currCircuit.begin()), currCircuit.begin() + 1, currCircuit.end());

        for (auto node : eulerianCircuit) {
            if (any_of(nodes[node]->adj.begin(), nodes[node]->adj.end(), [](Edge* edge) { return !edge->visited; })) {
                currCircuit.clear();
                currCircuit.push_back(node);
                break;
            }
        }
    }
}

void Graph::eulerianCircuitBacktracking(unsigned currNode, vector<unsigned> currCircuit, vector<unsigned>& eulerianCircuit) {

    if (currCircuit.size() == getNumberOfEdges()) {
        currCircuit.push_back(currNode);
        eulerianCircuit = currCircuit;
        return;
    }

    for (auto edge : nodes[currNode]->adj) {

        if (!edge->visited && eulerianCircuit.empty()) {
            edge->visited = true;
            unsigned nextNode = edge->first->id == currNode ? edge->second->id : edge->first->id;
            currCircuit.push_back(nextNode);

            eulerianCircuitBacktracking(nextNode, currCircuit, eulerianCircuit);

            edge->visited = false;
            currCircuit.pop_back();
        }
    }
}

double Graph::christofides(std::vector<unsigned>& path) {

    setAllDegreesTo0();
    path.clear();

    vector<pair<unsigned, unsigned>> mST;
    mSTPrim(mST);

    vector<Node*> oddDegreeNodes;

    for (auto node : nodes) {
        if (node->degree % 2 == 1) {
            oddDegreeNodes.push_back(node);
        }
    }

    priority_queue<Edge*, vector<Edge*>, decltype(compareEdges)> edges(compareEdges);

    for (auto node : oddDegreeNodes) {
        for (auto edge : node->adj) {

            unsigned next = edge->first->id == node->id ? edge->second->id : edge->first->id;

            if (!edge->visited && find(oddDegreeNodes.begin(), oddDegreeNodes.end(), nodes[next]) != oddDegreeNodes.end()) {
                edges.push(edge);
                edge->visited = true;
            }
        }
    }

    vector<Edge*> perfectEdges;

    while (perfectEdges.size() != oddDegreeNodes.size()/2) {

        Edge* edge = edges.top();
        edges.pop();

        if (!edge->first->visited && !edge->second->visited) {
            perfectEdges.push_back(edge);
            edge->first->visited = true;
            edge->second->visited = true;
        }
    }

    Graph multiGraph("multi" + this->name, realOrToy);

    for (auto node : nodes) {
        multiGraph.addNode(node->id);
    }

    for (auto edge : mST) {
        multiGraph.addEdge(edge.first, edge.second, findEdge(edge.first, edge.second)->distance);
    }

    for (auto edge : perfectEdges) {
        multiGraph.addEdge(edge->first->id, edge->second->id, edge->distance);
    }

    //vector<unsigned> currCircuit;
    //currCircuit.push_back(0);
    vector<unsigned> eulerianCircuit;

    bool isEulerian = all_of(multiGraph.nodes.begin(), multiGraph.nodes.end(), [](Node* node) { return node->degree % 2 == 0; });
    if (!isEulerian) return 0;

    //multiGraph.eulerianCircuitBacktracking(0, currCircuit, eulerianCircuit);
    multiGraph.eulerianCircuitHierholzer(eulerianCircuit);

    double distance = 0;
    path.push_back(0);
    unsigned last = 0;

    for (unsigned i = 1; i < eulerianCircuit.size() - 1; i++) {

        if (find(path.begin(), path.end(), eulerianCircuit[i]) == path.end()) {
            path.push_back(eulerianCircuit[i]);
            distance += findEdge(last, eulerianCircuit[i])->distance;
            last = eulerianCircuit[i];
        }
    }

    distance += findEdge(last, 0)->distance;
    path.push_back(0);

    return distance;
}


