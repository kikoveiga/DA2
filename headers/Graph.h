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
    };

    std::vector<Node*> nodes;

public:

    Graph(const std::string& name, bool realOrToy);
    void addNode(int id, float latitude = 0, float longitude = 0, const std::string& label = "");
    void addEdge(int first, int second, float distance);

    std::vector<Node*> getNodes() const;
};

#endif //DA2_GRAPH_H
