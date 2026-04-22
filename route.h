#ifndef ROUTE_H
#define ROUTE_H

#include "grid.h"

typedef struct route_node
{
    Station *station;
    struct route_node *next;
} route_node;

typedef struct{
    route_node *head;
    char routeName[50];
} Route;

Route *createRoute();
Route *getRouteByName(char *name);

void addRoute(Route *r);

void addStationToRoute(route_node **head, int x, int y);
void deleteStationFromRoute(route_node **head, int position);
void displayRoute(route_node *head);

int calculateDistance(route_node *head);
int calculate_cost(route_node *head);
int detectLoop(route_node *head);

void exportRoutes(char *filename);

#endif