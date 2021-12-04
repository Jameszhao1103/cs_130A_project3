#include <iostream>
#include <fstream>
#include <vector>
#include "GraphGenerator.h"
#include "GraphOperator.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> vertex;
    vector<int> edge;
    string line;
    ifstream myfile(argv[1]);
    while (getline(myfile, line))
    {
        int posOfComma = line.find(",");
        string el1 = line.substr(0, posOfComma);
        string el2 = line.substr(posOfComma + 1);
        vertex.push_back(stoi(el1));
        edge.push_back(stoi(el2));
    }
    GraphOperator graph;
    //GraphGenerator
    for (int i = 0; i < vertex.size(); i++)
    {
        graph.InsertEdge(vertex[i], edge[i]);
    }
    graph.InOrder();
    graph.PreOrder();
    graph.IsAcyclic();
    graph.ConnectedComponents();
    return 0;
};