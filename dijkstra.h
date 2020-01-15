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

using namespace std;

struct Vertex;

struct Edge {
    double weight;
    Vertex *from;
    Vertex *dest;
    explicit Edge(double _weight = 0, Vertex *_from = nullptr, Vertex *_dest = nullptr);
};

struct Vertex {
    string name = "";
    vector<Edge*> edges;
    explicit Vertex(string _name = "", vector<Edge*> _edges = {});
};

// To compare two edges
class EdgeComparator
{
public:
    int operator() (const Edge* edge1, const Edge* edge2);
};

class Dijkstra {
public:
    vector<string> findPath(Vertex &graph, string &source, string &destination);
};

#endif //TREE_DIJKSTRA_H
