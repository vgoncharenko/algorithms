//
// Created by Vitaliy on 2019-09-26.
//

#include "dijkstra.cpp"

void runTestDijkstra(std::string &variationName, Vertex root, std::string &src, std::string &dst, std::vector<std::string> &expected) {
  Dijkstra *solution = new Dijkstra();
  std::vector<std::string> result = solution->findPath(root, src, dst);
  for (int i = 0; i < expected.size(); ++i) {
    if (expected[i] != result[i])
      std::cout << "FAIL " + variationName + ": Dijkstra: \nresult[" << i << "] = '" << result[i] << "'\nexpected[" << i
           << "] = '" << expected[i] << "'" << std::endl;
  }
  std::cout << variationName + " SUCCESS!" << std::endl;
}

void dijkstraTest() {
  std::string variationName;
  Vertex *root = new Vertex();
  Edge *edge;
  std::vector<std::string> expected;
  std::string src, dst;

  variationName = "ex0";
  root->name = "A";
  src = "A";
  dst = "A";
  expected = {"A"};
    runTestDijkstra(variationName, *root, src, dst, expected);

  variationName = "ex1";
  root->name = "A";
  root->edges = {new Edge(1, root, new Vertex("B"))};
  src = "A";
  dst = "F";
  expected = {};
    runTestDijkstra(variationName, *root, src, dst, expected);

  variationName = "ex2";
  root->name = "A";
  Vertex *B = new Vertex("B");
  Vertex *D = new Vertex("D");
  Vertex *C = new Vertex("C");
  Vertex *E = new Vertex("E");
  Vertex *F = new Vertex("F");

  root->edges = {new Edge(1, root, B), new Edge(2, root, D)};
  B->edges = {new Edge(3, B, C), new Edge(5, B, E)};
  D->edges = {new Edge(3, D, E)};
  C->edges = {new Edge(1, C, E), new Edge(7, C, F)};
  E->edges = {new Edge(8, E, F)};

  src = "A";
  dst = "F";
  expected = {"A", "B", "C", "F"};
    runTestDijkstra(variationName, *root, src, dst, expected);
}
