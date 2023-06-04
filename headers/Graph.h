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
        Node* parent;
        int degree = 0;
    };

    std::vector<Node*> nodes;

public:

    /**
     * @brief Graph constructor
     * @param name of the graph
     * @param realOrToy boolean to know if the graph is real or toy
     */
    Graph(const std::string& name, bool realOrToy);

    /**
     * @brief Function to add a node to the graph's vector of nodes
     * @param id of the node
     * @param latitude of the node incase it's a real graph
     * @param longitude of the node incase it's a real graph
     * @param label of the node incase of the "tourism" graph
     */
    void addNode(unsigned id, double latitude = 0, double longitude = 0, const std::string& label = "");

    /**
     * @brief Function to add an edge
     * @param first node of the edge
     * @param second node of the edge
     * @param distance between the two nodes
     */
    void addEdge(unsigned first, unsigned second, double distance);

    /**
     * @brief Function to find an edge between two nodes
     * @param first node of the edge
     * @param second node of the edge
     * @return pointer to the edge or nullptr if it doesn't exist
     */
    Edge* findEdge(unsigned first, unsigned second);

    /**
     * @brief Function to get the name of the graph
     * @return string with the name of the graph
     */
    const std::string& getName() const;

    /**
     * @brief Function to get the graph's nodes
     * @return vector with the graph's nodes
     */
    const std::vector<Node*>& getNodes() const;

    /**
     * @brief Function to get the number of edges of the graph
     * @return unsigned with the number of edges of the graph
     */
    unsigned getNumberOfEdges() const;

    /**
     * @brief Function to set all the nodes of the graph as unvisited
     */
    void setAllNodesUnvisited();

    /**
     * @brief Function to set all the edges of the graph as unvisited
     */
    void setAllEdgesUnvisited();

    /**
     * @brief Function to set all the degrees of the graph's nodes to 0
     */
    void setAllDegreesTo0();

    /**
     * @brief Function to calculate the distance between two nodes' coordinates
     * @param first node
     * @param second node
     * @return distance
     */
    static double haversine(Node* first, Node* second);

    /**
     * @brief Function to get the boolean that tells if the graph is real or toy
     * @return boolean
     */
    bool isRealOrToy() const;

    /**
     * @brief Function that tells if the graph is complete
     * @return boolean
     */
    bool isComplete() const;

    /**
     * @brief Function that tells if the graph is connected
     * @return boolean
     */
    bool isConnected();

    /**
     * @brief Function that performs a standard DFS
     * @brief Complexity: O(|N| + |E|)
     * @param node to start the DFS from
     */
    void dfs(unsigned node);

    /**
     * @brief Function that performs a standard DFS and updates the DFS tree
     * @brief Complexity: O(|N| + |E|)
     * @param node to start the DFS from
     * @param tree DFS tree
     */
    void dfsTree(unsigned node, std::vector<unsigned>& tree);

    /**
     * @brief Function that performs a DFS adapted to find the articulation points of a graph
     * @brief Complexity: O(|N| + |E|)
     * @param node to start the DFS from
     * @param num array with the number of each node's visiting order
     * @param low array with the lowest number of each node's visiting order
     * @param counter to keep track of the visiting order
     * @param articulationPoints set with the articulation points
     */
    void dfsArticulationPoints(unsigned node, int num[], int low[], unsigned& counter, std::set<unsigned>& articulationPoints);

    /**
     * @brief Helper function that calls the DFS in order to find the articulation points
     * @return a set with the articulation points
     */
    std::set<unsigned> findArticulationPoints();

    /**
     * @brief Function that solves the TSP with backtracking
     * @brief Complexity: O(|N|!)
     * @param currNode
     * @param currPath
     * @param currDistance
     * @param minDistance
     * @param bestPath
     */
    void tSPBacktracking(unsigned currNode, std::vector<unsigned>& currPath, double currDistance, double& minDistance, std::vector<unsigned>& bestPath);

    /**
     * @brief Helper function that calls the TSP with backtracking
     * @param bestPath vector with the nodes of the best path
     * @return the distance of the best path
     */
    double solveTSPWithBacktracking(std::vector<unsigned>& bestPath);

    /**
     * @brief Function that solves the TSP with the Nearest Neighbour heuristic (similiar to Prim's algorithm)
     * @brief Complexity: O(|N|^2)
     * @param path vector with the nodes of the path
     * @return the distance of the path
     */
    double tSPNNHeuristic(std::vector<unsigned>& path);

    /**
     * @brief Function that solves the TSP with the Greedy heuristic (similiar to Kruskal's algorithm)
     * @brief Complexity: O(|N|^2)
     * @param path vector with the nodes of the path
     * @return the distance of the path
     */
    double tSPGreedyHeuristic(std::vector<std::pair<unsigned, unsigned>>& path);

    /**
     * @brief Function that calculates the Minimum Spanning Tree with Prim's algorithm
     * @brief Complexity: O((|N| + |E|)log|N|)
     * @param mST vector with the edges of the MST
     * @return the distance of the MST
     */
    double mSTPrim(std::vector<std::pair<unsigned, unsigned>>& mST);

    /**
     * @brief Function that finds the parent of a node in the Kruskal's algorithm
     * @brief Complexity: O(|E|log|E|)
     * @param parent array with the parents of each node
     * @param component node to find the parent of
     * @return the parent of the node
     */
    unsigned findParentKruskal(unsigned parent[], unsigned component);

    /**
     * @brief Function that unions two sets in the Kruskal's algorithm
     * @param set1 number of the first set
     * @param set2 number of the second set
     * @param parent array with the parent of each node
     * @param rank array with the rank of each node
     */
    void unionSetKruskal(unsigned set1, unsigned set2, unsigned parent[], unsigned rank[]);

    /**
     * @brief Function that calculates the Minimum Spanning Tree with Kruskal's algorithm
     * @brief Complexity: O(|E|log|E|)
     * @param mST vector with the edges of the MST
     * @return
     */
    double mSTKruskal(std::vector<std::pair<unsigned, unsigned>>& mST);

    /**
     * @brief Function that solves the TSP with the 2-Approximation triangle inequality heuristic
     * @brief Complexity: O((|N| + |E|)log|N|)
     * @param path vector with the nodes of the path
     * @return the distance of the path
     */
    double tSP2Approximation(std::vector<unsigned>& path);

    /**
     * @Function that finds a lower bound for the TSP optimal solution calling Prim's algorithm for every node
     * @brief Complexity: O((|N| + |E|)log|N|*|N|)
     * @param tree vector with the edges of the tree
     * @return the distance of the tree
     */
    double tSP1TreeLowerBound(std::vector<std::pair<unsigned, unsigned>>& tree);

    /**
     * @brief Hierholzer's algorithm to find the Eulerian circuit of an eulerian graph
     * @brief Complexity: O(|E|)
     * @param eulerianCircuit vector with the nodes of the eulerian circuit
     */
    void eulerianCircuitHierholzer(std::vector<unsigned>& eulerianCircuit);

    /**
     * @brief Backtracking algorithm to find the Eulerian circuit of an eulerian graph (less efficient so it was not used)
     * @param currNode
     * @param currCircuit
     * @param eulerianCircuit
     */
    void eulerianCircuitBacktracking(unsigned currNode, std::vector<unsigned> currCircuit, std::vector<unsigned>& eulerianCircuit);

    /**
     * @brief Function that implements the Christofides' heuristic to find a good approximation for the TSP
     * @brief Complexity: O(|N|^3)
     * @param path vector with the nodes of the path
     * @return the distance of the path
     */
    double christofides(std::vector<unsigned>& path);

    /**
     * @brief Function that implements the 2-Opt algorithm to improve a path by switching pairs of edges
     * @param path vector with the nodes of the path
     * @return the best improved distance of the path
     */
    double tSP2OptImprovement(std::vector<unsigned>& path);
};

#endif //DA2_GRAPH_H
