#pragma once
#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct Cell {
    int number_of_mines;
    char ch;
    bool uncovered;
    bool bomb;
}Cell;

/* struct members for height and width of board and 2 dimensional array of cells */
typedef struct Board {
    int height, width;
    Cell** cells; /* pointer to the pointer */
}Board;

struct Creds {
	char Name[32];
	int wins;
    int loses;
	float time;
};


#endif
