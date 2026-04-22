#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route.h"

// ROUTE = Linked List of Stations
// route_node -> contains pointer to a Station
// routes[] -> array of Route*
// routeCount -> how many routes currently exist

#define MAX_ROUTES 50

static Route *routes[MAX_ROUTES];
static int routeCount = 0;

// Allocates and initializes a new Route structure with an empty linked list.
// Stores the route in a global array and returns a pointer to it.
Route *createRoute()
{
    Route *r = (Route *)malloc(sizeof(Route));
    if (!r) return NULL;

    r->head = NULL;
    r->routeName[0] = '\0';

    return r;
}

void addRoute(Route *r){
    routes[routeCount++] = r;
}

// Searches through all stored routes to find one matching the given name.
// Returns a pointer to the matching Route, or NULL if not found.
Route *getRouteByName(char *name)
{
    for (int i = 0; i < routeCount; i++)
        if (strcmp(routes[i]->routeName, name) == 0)
            return routes[i];
    return NULL;
}

// Creates a new linked list node for a given station.
// Initializes the node with station data and sets next to NULL.
route_node *createNode(Station *s)
{
    if (s == NULL) return NULL;

    route_node *n = (route_node *)malloc(sizeof(route_node));
    if (!n) return NULL;

    n->station = s;
    n->next = NULL;

    return n;
}

// Adds a station (by coordinates) to the end of a route linked list.
// Validates the station and updates the head if the list is initially empty.
void addStationToRoute(route_node **head, int x, int y)
{
    Station *s = get_station(x, y);
    if (!s || !s->name) // validation
        return;

    route_node *n = createNode(s);

    if (!*head)
    {
        *head = n;
        return;
    }
//  attaching the node at the end
    route_node *t = *head;
    while (t->next)
        t = t->next;
    t->next = n;
}

// Deletes a station from the route at the specified position.
// Adjusts linked list pointers and frees memory of the removed node.
void deleteStationFromRoute(route_node **head, int position)
{
    if (!head || !*head) return;

    route_node *temp = *head;

    // Delete head node
    if (position == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse to node before position
    for (int i = 0; temp && i < position - 1; i++)
        temp = temp->next;

    if (!temp || !temp->next) return;

    route_node *toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
}

// Traverses the route linked list and prints each station in order.
// Displays the path in a readable (x,y:name) → format.
void displayRoute(route_node *head)
{
    printf("\n==============================\n");
    printf(" ROUTE DETAILS\n");
    printf("==============================\n");

    while (head)
    {
        printf("(%d,%d:%s)", head->station->x, head->station->y, head->station->name);
        if (head->next)
            printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

// Computes total distance of the route using Manhattan distance between stations.
// Iterates through consecutive nodes and accumulates coordinate differences.
int calculateDistance(route_node *head)
{
    int d = 0;
    while (head && head->next)
    {
        d += abs(head->station->x - head->next->station->x) + abs(head->station->y - head->next->station->y);
        head = head->next;
    }
    printf("\n ROUTE METRICS\n");
    printf("------------------------------\n");
    return d;
}

// Calculates total cost of the route based on a fixed cost per station.
// Traverses all nodes and sums a constant value for each stop.
int calculate_cost(route_node *head)
{
    int cost = 0;
    while (head)
    {
        cost += 5;
        head = head->next;
    }
    return cost;
}

// Detects if the route contains a cycle using Floyd’s cycle detection algorithm.
// Uses slow and fast pointers to determine if a loop exists in the list.
int detectLoop(route_node *head)
{
    route_node *s = head, *f = head;

    while (f && f->next)
    {
        s = s->next;
        f = f->next->next;

        if (s == f)
        {
            printf("\n LOOP DETECTED in route\n");
            return 1;
        }
    }
    return 0;
}

// Writes all stored routes and their station sequences to a file.
// Iterates through each route and prints its path in a structured format.
void exportRoutes(char *filename)
{
    FILE *fp = fopen(filename, "w");

    for (int i = 0; i < routeCount; i++)
    {
        fprintf(fp, "Route %s:\n", routes[i]->routeName);
        route_node *t = routes[i]->head;

        while (t)
        {
            fprintf(fp, "(%d,%d:%s)", t->station->x, t->station->y, t->station->name);
            if (t->next)
                fprintf(fp, " -> ");
            t = t->next;
        }
        fprintf(fp, "\n\n");
    }
    fclose(fp);
}