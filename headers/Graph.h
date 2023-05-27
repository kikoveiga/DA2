//
// Created by kikoveiga on 29-04-2023.
//

#ifndef DA2_GRAPH_H
#define DA2_GRAPH_H

#include <vector>
#include <string>

class Graph {

private:

    std::string name;
    bool realOrToy;

    struct Node;

    struct Edge {
        Node* first;
        Node* second;
        float distance;
    };

    struct Node {
        int id;
        std::vector<Edge*> adj = {};
        float latitude;
        float longitude;
        std::string label;
        bool visited = false;
    };

    std::vector<Node*> nodes;

public:

    Graph(const std::string& name, bool realOrToy);
    void addNode(int id, float latitude = 0, float longitude = 0, const std::string& label = "");
    void addEdge(int first, int second, float distance);

    const std::string& getName() const;
    bool isRealOrToy() const;
    const std::vector<Node*>& getNodes() const;
    unsigned getNumberOfEdges() const;
    /**
     * @brief This function should solve the TSP with backtracking
     * Backtracking can be used to solve the TSP,
     * but it becomes computationally infeasible for larger graphs due to the exponential growth in the number of
     * possible tours to explore.
     * @return
     */
    int solveTspWithBacktracking();
    /**
     * @brief sets all nodes visited field to false
     */
    void setAllNodesUnvisited();


};

#endif //DA2_GRAPH_H
