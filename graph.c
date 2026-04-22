#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "grid.h"

#define MAX 100


//   GRAPH STRUCTURES

typedef struct Edge
{
    int x, y;
    int distance;
    int cost;
    char transport[20];
    struct Edge *next;
} Edge;

typedef struct
{
    Edge *head;
} GraphNode;

static GraphNode **graph;
static int ROWS, COLS;

//   PRIORITY QUEUE

typedef struct
{
    int x, y;
    int cost;
} PQNode;

PQNode heap[1000];
int heapSize = 0;

void swap(PQNode *a, PQNode *b)
{
    PQNode t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(int i)
{
    while (i > 0 && heap[(i - 1) / 2].cost > heap[i].cost)
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapifyDown(int i)
{
    int smallest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if (l < heapSize && heap[l].cost < heap[smallest].cost)
        smallest = l;
    if (r < heapSize && heap[r].cost < heap[smallest].cost)
        smallest = r;

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void push(int x, int y, int cost)
{
    heap[heapSize] = (PQNode){x, y, cost};
    heapifyUp(heapSize);
    heapSize++;
}

PQNode pop()
{
    PQNode root = heap[0];
    heap[0] = heap[--heapSize];
    heapifyDown(0);
    return root;
}

// Initializes graph data structures based on grid dimensions.
// Prepares memory or structures required to represent nodes and edges.

void initializeGraph(int rows, int cols)
{
    ROWS = rows;
    COLS = cols;

    graph = malloc(rows * sizeof(GraphNode *));
    for (int i = 0; i < rows; i++)
    {
        graph[i] = malloc(cols * sizeof(GraphNode));
        for (int j = 0; j < cols; j++)
            graph[i][j].head = NULL;
    }
    printf("Graph initialized: %d x %d\n", ROWS, COLS);
}

// Adds an edge between two stations with distance, cost, and transport type.
// Used internally while building the graph, but exposed for flexibility.

void addEdge(int x1, int y1, int x2, int y2, int dist, int cost, char *type)
{

    Edge *e = malloc(sizeof(Edge));
    e->x = x2;
    e->y = y2;
    e->distance = dist;
    e->cost = cost;
    strcpy(e->transport, type);

    e->next = graph[x1][y1].head;
    graph[x1][y1].head = e;
}

// Builds the graph by connecting adjacent stations in the grid.
// Adds edges between valid neighboring stations based on movement rules.
void buildGraph()
{

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {

            Station *s = get_station(i, j);
            if (!s || !s->name)
                continue;

            for (int k = 0; k < 4; k++)
            {
                int ni = i + dx[k];
                int nj = j + dy[k];

                if (ni >= 0 && nj >= 0 && ni < ROWS && nj < COLS)
                {

                    Station *t = get_station(ni, nj);
                    if (!t || !t->name)
                        continue;

                    if (strstr(s->types, "METRO") && strstr(t->types, "METRO"))
                        addEdge(i, j, ni, nj, 1, 2, "METRO");

                    else if (strstr(s->types, "BUS") && strstr(t->types, "BUS"))
                        addEdge(i, j, ni, nj, 1, 5, "BUS");

                    else
                        addEdge(i, j, ni, nj, 1, 8, "AUTO");
                }
            }
        }
    }
}

// Recursively or iteratively reconstructs and prints the path.
// Uses parent tracking arrays to trace from destination to source.
void printPath(int px[][COLS], int py[][COLS], int x, int y)
{

    if (px[x][y] == -1 && py[x][y] == -1)
    {
        printf("(%d,%d)", x, y);
        return;
    }

    printPath(px, py, px[x][y], py[x][y]);
    printf(" -> (%d,%d)", x, y);
}

void markPath(int path[][COLS], int px[][COLS], int py[][COLS], int x, int y)
{

    while (!(px[x][y] == -1 && py[x][y] == -1))
    {
        path[x][y] = 1;
        int tx = px[x][y];
        int ty = py[x][y];
        x = tx;
        y = ty;
    }
    path[x][y] = 1;
}

// Displays a visual representation of the path on the grid.
// Marks path cells distinctly from non-path cells.
void displayPathGrid(int path[][COLS])
{
    printf("\n==============================\n");
    printf(" PATH VISUALIZATION\n");
    printf("==============================\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (path[i][j])
                printf(" * ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

// Computes and displays the shortest path between two stations.
// Also prints path details and visual representation on the grid.

void findShortestPathDetailed(int sx, int sy, int ex, int ey)
{
    printf("\n==============================\n");
    printf(" SHORTEST PATH RESULT\n");
    printf("==============================\n\n");
    int dist[ROWS][COLS];
    int px[ROWS][COLS];
    int py[ROWS][COLS];
    char trans[ROWS][COLS][20];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            dist[i][j] = INT_MAX;
            px[i][j] = -1;
            py[i][j] = -1;
            strcpy(trans[i][j], "");
        }
    }

    dist[sx][sy] = 0;
    heapSize = 0;
    push(sx, sy, 0);

    while (heapSize)
    {

        PQNode curr = pop();
        int ux = curr.x, uy = curr.y;

        Edge *e = graph[ux][uy].head;

        while (e)
        {

            int vx = e->x, vy = e->y;
            int newCost = dist[ux][uy] + e->cost;

            if (strlen(trans[ux][uy]) > 0 &&
                strcmp(trans[ux][uy], e->transport) != 0)
                newCost += 10;

            if (newCost < dist[vx][vy])
            {

                dist[vx][vy] = newCost;
                px[vx][vy] = ux;
                py[vx][vy] = uy;
                strcpy(trans[vx][vy], e->transport);

                push(vx, vy, newCost);
            }

            e = e->next;
        }
    }

    printf("\nSHORTEST PATH:\n");
    printPath(px, py, ex, ey);

    printf("\nTotal Cost: %d \n", dist[ex][ey]);

    int path[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            path[i][j] = 0;
        }
    }
    markPath(path, px, py, ex, ey);
    displayPathGrid(path);
}