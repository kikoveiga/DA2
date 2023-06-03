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
    Graph* buildToyGraph(const std::string& filename, const std::string& path);
    Graph* buildRealWorldGraph(unsigned number);
    void buildRealWorldGraphNodes(unsigned number);
    void buildRealWorldGraphEdges(unsigned number);


    const std::vector<Graph*>& getGraphs();
};

#endif //DA2_UTILS_H
