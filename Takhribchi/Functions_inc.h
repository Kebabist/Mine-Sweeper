#pragma once
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "Structs.h"

int Logic();
void make_board(Board*); /* pointer to the board in order to create board */
void print_board(Board*); /* pointer to the board and printing board */
void bombplacing_randomly(Board*, int); /* pointer to the board and number of bombs  */
void numof_adjacent_mines(Board*); /* pointer to the board and determining number of bombs in adjacency cells */
void uncover(Board*, int, int); /* pointer to the board and selected coordinates by the user for uncovering cells */
void reveal_automatically(Board*, int, int); /* pointer to the board and cell's coordinates for automatic reveal of cells */
void check_for_win(Board*, int); /* pointer to the board and number of mines  */
void play_game(); /* function to play the game */
void printmenu();
void newgame();
void console_size();
void printwlc();
void profile();
void WritetomyFile();
void readfile();
void checkminelimit(Board* ptr, int mines);
void cheat(Board* ptr, int a, int b);


#endif