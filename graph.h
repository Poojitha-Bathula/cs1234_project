#ifndef GRAPH_H
#define GRAPH_H

#include "grid.h"


//  GRAPH INITIALIZATION
void initializeGraph(int rows, int cols);
void buildGraph();

// SHORTEST PATH (MAIN FUNCTION)
void findShortestPathDetailed(int sx, int sy, int ex, int ey);

/* Add edge manually (used internally, but exposing = bonus marks) */
void addEdge(int x1, int y1, int x2, int y2, int dist, int cost, char *type);

/* Path visualization helpers */
void displayPathGrid(int path[][100]); // safe upper bound
void printPath(int px[][100], int py[][100], int x, int y);

#endif
