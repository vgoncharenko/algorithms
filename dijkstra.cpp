//
// Created by Vitaliy on 2019-09-25.
//

#include "dijkstra.h"

Edge::Edge(double _weight, Vertex *_from, Vertex *_dest){
  weight = _weight;
  from = _from;
  dest = _dest;
}

Vertex::Vertex(std::string _name, std::vector<Edge*> _edges){
  name = _name;
  edges = _edges;
}

int EdgeComparator::operator()(const Edge* edge1, const Edge* edge2) {
  return edge1->weight > edge2->weight;
}

std::vector<std::string> Dijkstra::findPath(Vertex &root, std::string &source, std::string &destination){
  if (source == destination)
    return std::vector<std::string>{source};

  std::vector<std::string> path = {};
    std::map<std::string, std::string> minPaths;
    std::priority_queue<Edge*, std::vector<Edge*>, EdgeComparator> minHeap;
    std::map<std::string, uint8_t> distance;
  Edge *tempEdge;

  distance[source] = 0;
  for (int i = 0; i < root.edges.size(); ++i) {
    minHeap.push(root.edges[i]);
  }

  while (!minHeap.empty()) {
    tempEdge = minHeap.top();
    minHeap.pop();
    if (distance.find(tempEdge->dest->name) == distance.end()) {
      distance[tempEdge->dest->name] = tempEdge->weight;
      minPaths[tempEdge->dest->name] = tempEdge->from->name;
      for (int i = 0; i < tempEdge->dest->edges.size(); ++i) {
        tempEdge->dest->edges[i]->weight += distance[tempEdge->dest->name];
        minHeap.push(tempEdge->dest->edges[i]);
      }
    }
    if(distance[tempEdge->dest->name] > tempEdge->weight) {
      distance[tempEdge->dest->name] = tempEdge->weight;
      minPaths[tempEdge->dest->name] = tempEdge->from->name;
      for (int i = 0; i < tempEdge->dest->edges.size(); ++i) {
        tempEdge->dest->edges[i]->weight += tempEdge->weight;
        minHeap.push(tempEdge->dest->edges[i]);
      }
    }

  }

  std::string item = destination;
  while ("" != item && item != source) {
    path.push_back(item);
    item = minPaths[item];
  }
  path.push_back(source);

  reverse(path.begin(),path.end());

  return path;
}

