#ifndef GRID_H
#define GRID_H

#include <stdio.h>

typedef struct
{
    char *name;
    char *types;
    int typeCount;
    int x, y;
} Station;

void initializeGrid(int rows, int cols);
void load_Grid(FILE *fp);
void display_stations();
void displayGridVisual();

void rename_station(int x, int y, char *name);
Station *get_station(int x, int y);
void search_station_by_name(char *name);

#endif