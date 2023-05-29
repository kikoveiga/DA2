//
// Created by kikoveiga on 29-04-2023.
//

#ifndef DA2_UTILS_H
#define DA2_UTILS_H

#include <vector>
#include <fstream>
#include <sstream>

#include "Graph.h"

class Utils {

private:
    std::vector<Graph*> graphs;

public:

    Utils();

    void buildGraphs();
    Graph* buildRealWorldGraph(int number);
    void buildRealWorldGraphNodes(int number);
    void buildRealWorldGraphEdges(int number);
    Graph* buildToyGraph(const std::string& filename, const std::string& path);

    const std::vector<Graph*>& getGraphs();
};

#endif //DA2_UTILS_H
