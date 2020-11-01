//
// Created by Vitaliy on 2019-09-25.
// https://www.youtube.com/watch?v=tyQSgTytc4s
//

#ifndef TREE_DIJKSTRA_H
#define TREE_DIJKSTRA_H

#include <vector>
#include <queue>
#include <map>
#include <iostream>


struct Vertex;

struct Edge {
    double weight;
    Vertex *from;
    Vertex *dest;
    explicit Edge(double _weight = 0, Vertex *_from = nullptr, Vertex *_dest = nullptr);
};

struct Vertex {
    std::string name = "";
    std::vector<Edge*> edges;
    explicit Vertex(std::string _name = "", std::vector<Edge*> _edges = {});
};

// To compare two edges
class EdgeComparator
{
public:
    int operator() (const Edge* edge1, const Edge* edge2);
};

class Dijkstra {
public:
    std::vector<std::string> findPath(Vertex &graph, std::string &source, std::string &destination);
};

#endif //TREE_DIJKSTRA_H
