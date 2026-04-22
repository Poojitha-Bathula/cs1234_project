#include <stdio.h>
#include <string.h>
#include "grid.h"
#include "route.h"
#include "graph.h"

int main()
{
    printf("Program started\n");
    FILE *fp = fopen("stations.txt", "r");
    int r, c;
    fscanf(fp, "%d %d", &r, &c);

    initializeGrid(r, c);
    load_Grid(fp);
    fclose(fp);

   // display_stations();
   // displayGridVisual();

    initializeGraph(r, c);
    buildGraph();

    FILE *fin = fopen("input.txt", "r");
    char cmd[50];

    while (fscanf(fin, "%s", cmd) != EOF)
    {
        if (cmd[0] == '#')
        {
            char skip[200];
            fgets(skip, sizeof(skip), fin);
            continue;
        }
        //  Ignore comments

        // ---------------- DISPLAY ----------------
        if (strcmp(cmd, "display") == 0)
        {
            display_stations();
        }

        // ---------------- SHORTEST PATH ----------------
        else if (strcmp(cmd, "shortest") == 0)
        {
            int sx, sy, ex, ey;
            fscanf(fin, "%d %d %d %d", &sx, &sy, &ex, &ey);
            findShortestPathDetailed(sx, sy, ex, ey);
        }

        // ---------------- SEARCH ----------------
        else if (strcmp(cmd, "search") == 0)
        {
            char name[50];
            fscanf(fin, "%s", name);
            search_station_by_name(name);
        }

        // ---------------- RENAME ----------------
        else if (strcmp(cmd, "rename") == 0)
        {
            int x, y;
            char name[50];
            fscanf(fin, " %d %d %s", &x, &y, name);
            rename_station(x, y, name);
}

        // ---------------- CREATE ROUTE ----------------
        else if (strcmp(cmd, "create_route") == 0)
        {
            char name[50];
            fscanf(fin, "%s", name);
            Route *r = createRoute();
            strcpy(r->routeName, name);
            addRoute(r);
        }

        // ---------------- ADD STATION ----------------
        else if (strcmp(cmd, "add_station") == 0)
        {
            char name[50];
            int x, y;

            fscanf(fin, " %s %d %d",name,&x, &y);

            Route *r = getRouteByName(name);
            if (r)
                addStationToRoute(&r->head, x, y);
            else
                printf("Route not found\n");
        }

        // ---------------- DISPLAY ROUTE ----------------
        else if (strcmp(cmd, "display_route") == 0)
        {
            char name[50];
            fscanf(fin, "%s", name);

            Route *r = getRouteByName(name);
            if (r)
                displayRoute(r->head);
            else
                printf("Route not found\n");
        }

        // ---------------- DISTANCE ----------------
        else if (strcmp(cmd, "distance") == 0)
        {
            char name[50];
            fscanf(fin, "%s", name);

            Route *r = getRouteByName(name);
            if (r)
                printf("Distance: %d\n", calculateDistance(r->head));
            else
                printf("Route not found\n");
        }

        // ---------------- COST ----------------
        else if (strcmp(cmd, "cost") == 0)
        {
            char name[50];
            fscanf(fin, "%s", name);

            Route *r = getRouteByName(name);
            if (r)
                printf("Cost: %d\n", calculate_cost(r->head));
            else
                printf("Route not found\n");
        }

        // ---------------- LOOP DETECTION ----------------
        else if (strcmp(cmd, "detect_loop") == 0)
        {
            char name[50];
            fscanf(fin, "%s", name);

            Route *r = getRouteByName(name);
            if (r)
            {
                if (detectLoop(r->head))
                    printf("Loop detected\n");
                else
                    printf("No loop\n");
            }
            else
                printf("Route not found\n");
        }

        // ---------------- DELETE ----------------
        else if (strcmp(cmd, "delete") == 0)
        {
            char name[50];
            int pos;

            fscanf(fin, "%s %d", name, &pos);

            Route *r = getRouteByName(name);
            if (r)
                deleteStationFromRoute(&r->head, pos);
            else
                printf("Route not found\n");
        }
    }

    fclose(fin);

    exportRoutes("output_routes.txt");

    return 0;
}