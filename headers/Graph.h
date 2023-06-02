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
#include <stack>

class Graph {

private:

    std::string name;
    bool realOrToy;

    struct Node;

    struct Edge {
        Node* first;
        Node* second;
        double distance;
        bool visited;
    };

    struct Node {
        unsigned id;
        std::vector<Edge*> adj = {};
        double latitude = 0;
        double longitude = 0;
        std::string label;
        bool visited = false;
        double key = std::numeric_limits<double>::infinity();
        Node* parent;
        unsigned degree = 0;
    };

    std::vector<Node*> nodes;

public:

    Graph(const std::string& name, bool realOrToy);

    void addNode(unsigned id, double latitude = 0, double longitude = 0, const std::string& label = "");
    void addEdge(unsigned first, unsigned second, double distance);
    Edge* findEdge(unsigned first, unsigned second);

    const std::string& getName() const;
    const std::vector<Node*>& getNodes() const;
    unsigned getNumberOfEdges() const;

    bool isRealOrToy() const;
    bool isComplete() const;
    bool isConnected();

    void dfs(unsigned node);
    void dfsTree(unsigned node, std::vector<unsigned>& tree);
    void setAllNodesUnvisited();
    void setAllDegreesTo0();
    static double haversine(Node* first, Node* second);

    std::vector<unsigned> findArticulationPoints();

    /**
     * @brief Backtracking function to find the optimal TSP tour
     * @param current
     * @param tour
     * @param minCost
     * @param depth
     */
    void tSPBacktracking(unsigned currNode, std::vector<unsigned>& currPath, double currDistance, double& minDistance, std::vector<unsigned>& bestPath);
    /**
     * @brief This function should solve the TSP with backtracking
     * Backtracking can be used to solve the TSP,
     * but it becomes computationally infeasible for larger graphs due to the exponential growth in the number of
     * possible tours to explore.
     * @return
     */
    double solveTSPWithBacktracking(std::vector<unsigned>& bestPath);

    double tSPNNHeuristic(std::vector<unsigned>& path);
    double tSPGreedyHeuristic(std::vector<std::pair<unsigned, unsigned>>& path);

    double mSTPrim(std::vector<std::pair<unsigned, unsigned>>& mST);
    double mSTKruskal(std::vector<std::pair<unsigned, unsigned>>& mST);
    unsigned findParentKruskal(unsigned parent[], unsigned component);
    void unionSetKruskal(unsigned set1, unsigned set2, unsigned parent[], unsigned rank[]);

    double tSP2Approximation(std::vector<unsigned>& path);

    double tSP1TreeLowerBound(std::vector<std::pair<unsigned, unsigned>>& tree);

    void eulerianCircuitHierholzer(std::vector<unsigned>& eulerianCircuit);
    void eulerianCircuitBacktracking(unsigned currNode, std::vector<unsigned> currCircuit, std::vector<unsigned>& eulerianCircuit);
    double christofides(std::vector<unsigned>& path);

};

#endif //DA2_GRAPH_H
