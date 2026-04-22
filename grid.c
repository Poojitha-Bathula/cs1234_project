#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grid.h"

// grid -> array of row pointers
// grid[i] -> array of Stations
// grid[i][j] -> actual station

static Station **grid;
static int ROWS, COLS;

void initializeGrid(int rows, int cols)
{
    ROWS = rows;
    COLS = cols;

    grid = malloc(rows * sizeof(Station *));

    for (int i = 0; i < rows; i++)
    {
        grid[i] = malloc(cols * sizeof(Station));

        for (int j = 0; j < cols; j++)
        {
            grid[i][j].name = NULL;
            grid[i][j].types = NULL;
            grid[i][j].typeCount = 0;
            grid[i][j].x = i;
            grid[i][j].y = j;
            //printf("A\n");
        }
    }
}

void load_Grid(FILE *fp)
{
    int x, y;
    char name[50], types[100];

    while (fscanf(fp, "%d %d %s %[^\n]", &x, &y, name, types) != EOF)
    {

        grid[x][y].name = malloc(strlen(name) + 1);
        strcpy(grid[x][y].name, name);

        grid[x][y].types = malloc(strlen(types) + 1);
        strcpy(grid[x][y].types, types);

        int count = 1;
        for (int i = 0; types[i]; i++)
            if (types[i] == ',')
                count++;

        grid[x][y].typeCount = count;
        
    }
}

Station *get_station(int x, int y)
{
    if (x < 0 || y < 0 || x >= ROWS || y >= COLS)
        return NULL;
    return &grid[x][y];
//returns address of station
}

void rename_station(int x, int y, char *name)
{
    Station *s = get_station(x, y);
    if (!s)
        return;

    free(s->name);
    s->name = malloc(strlen(name) + 1);
    strcpy(s->name, name);
}

void search_station_by_name(char *name)
{
    printf("\n SEARCH RESULT\n");
    printf("------------------------------\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid[i][j].name && strcmp(grid[i][j].name, name) == 0)
            {
                printf("Found at (%d,%d)\n", i, j);
                return;
            }
        }
    }
    printf(" Station '%s' not found\n", name);
}

void display_stations()
{
    printf("\n==============================\n");
    printf(" AVAILABLE STATIONS\n");
    printf("==============================\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid[i][j].name){
                printf("%s\n", grid[i][j].name);
            }
            else{
                printf("[----]");
            }
        }
        
    }
}

void displayGridVisual()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid[i][j].name)
                printf("%-8s\n", grid[i][j].name);
            else
                printf("--------");
        }
        printf("\n");
    }
}
