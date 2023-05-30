//
// Created by kikoveiga on 29-04-2023.
//

#ifndef DA2_GRAPH_H
#define DA2_GRAPH_H

#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

class Graph {

private:

    std::string name;
    bool realOrToy;

    struct Node;

    struct Edge {
        Node* first;
        Node* second;
        double distance;
    };

    struct Node {
        unsigned id;
        std::vector<Edge*> adj = {};
        double latitude;
        double longitude;
        std::string label;
        bool visited = false;
        double key = std::numeric_limits<double>::infinity();
        int parentNode = -1;
    };

    std::vector<Node*> nodes;

public:

    Graph(const std::string& name, bool realOrToy);
    void addNode(unsigned id, double latitude = 0, double longitude = 0, const std::string& label = "");
    void addEdge(unsigned first, unsigned second, double distance);
    Edge* findEdge(unsigned first, unsigned second);

    const std::string& getName() const;
    bool isRealOrToy() const;
    bool isComplete() const;
    bool isConnected();
    void dfs(unsigned node);
    const std::vector<Node*>& getNodes() const;
    unsigned getNumberOfEdges() const;



    /**
     * @brief sets all nodes visited field to false
     */
    void setAllNodesUnvisited();
    void setAllKeysToInfinity();
    static double haversine(Node* first, Node* second);

    /**
     * @brief Backtracking function to find the optimal TSP tour
     * @param current
     * @param tour
     * @param minCost
     * @param depth
     */
    void tspBacktracking(unsigned currNode, std::vector<unsigned>& currPath, double currDistance, double& minDistance, unsigned depth, std::vector<unsigned>& bestPath);
    /**
     * @brief This function should solve the TSP with backtracking
     * Backtracking can be used to solve the TSP,
     * but it becomes computationally infeasible for larger graphs due to the exponential growth in the number of
     * possible tours to explore.
     * @return
     */
    double solveTspWithBacktracking(std::vector<unsigned>& path, std::vector<unsigned>& bestPath);

    double tspNNHeuristic(std::vector<unsigned>& path);

    double mSTPrim(std::vector<std::pair<unsigned, unsigned>>& mstEdges);
    double mSTKruskal(std::vector<std::pair<unsigned, unsigned>>& mstEdges);

    unsigned findParentKruskal(unsigned parent[], unsigned component);
    void unionSetKruskal(unsigned set1, unsigned set2, unsigned parent[], unsigned rank[]);


};

#endif //DA2_GRAPH_H
