//
// Created by teenspirit on 12/18/22.
//

#ifndef BICONNECTED_GRAPH_SRC_GRAPHMATRIX_H_
#define BICONNECTED_GRAPH_SRC_GRAPHMATRIX_H_

#include "GraphForm.h"
#include <vector>

using namespace std;

template<class Vertex, class Edge>
class GraphMatrix : public GraphForm<Vertex, Edge> {
 public:
  bool isDirected;
  GraphMatrix(bool D){
    isDirected = D;
  }
  bool InsertVertex(int index) override {
    int size = matrix.size();
    if (index < 0 || index > size)
      return false;
    vector<Edge *> newLine;
    newLine.assign(size, NULL);
    matrix.insert(matrix.begin() + index, newLine);
    size++;
    for (int i = 0; i < size; ++i) {
      matrix[i].insert(matrix[i].begin() + index, (Edge *) NULL);
    }
    return true;
  }

  bool DeleteVertex(int index) override {
    int size = matrix.size();
    if (index < 0 || index >= size)
      return false;
    matrix.erase(matrix.begin() + index);
    size--;
    for (int i = 0; i < size; ++i) {
      matrix[i].erase(matrix[i].begin() + index);
    }
    return true;
  }

  bool InsertEdge(int v1, int v2, Edge *e) override {
    int size = matrix.size();
    // incorrect vertex number
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
    // existing edge
    if (v1 == v2 || matrix[v1][v2] != NULL) return false;
    // insert
    matrix[v1][v2] = e;
    return true;
  }

  bool DeleteEdge(int v1, int v2) override {

    int size = matrix.size();
    // incorrect vertex number
    if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
    // Vertex isn't existing
    if (v1 == v2 || matrix[v1][v2] == NULL) return false;
    matrix[v1][v2] = NULL;
    return true;
  }

 private:
  vector<vector<Edge *>> matrix;
};

#endif //BICONNECTED_GRAPH_SRC_GRAPHMATRIX_H_
