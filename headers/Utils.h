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
    /**
     * @brief Default Utils constructor which calls the buildGraphs function
     */
    Utils();

    /**
     *@brief Function that calls the buildToyGraph and buildRealWorldGraph functions for each real/toy graph
     */
    void buildGraphs();

    /**
     * @brief Function to parse the information from each toy graph csv to the graph object
     * @param filename string with the name of the file to read the graph from
     * @param path string with the path of the file to read the graph from
     * @return Graph* pointer to the graph created
     */
    Graph* buildToyGraph(const std::string& filename, const std::string& path);

    /**
     * @brief Function that creates the graph object and calls the buildRealWorldGraphNodes and buildRealWorldGraphEdges functions
     * @param number of the graph
     * @return Graph* pointer to the graph created
     */
    Graph* buildRealWorldGraph(unsigned number);

    /**
     * @brief Function to parse the information from each real world graph's nodes csv to the graph object
     * @param number of the graph
     */
    void buildRealWorldGraphNodes(unsigned number);

    /**
     * @brief Function to parse the information from each real world graph's edges csv to the graph object
     * @param number of the graph
     */
    void buildRealWorldGraphEdges(unsigned number);

    /**
     * @brief Get function for the vector of graphs
     * @return vector with the graphs
     */
    const std::vector<Graph*>& getGraphs();
};

#endif //DA2_UTILS_H
