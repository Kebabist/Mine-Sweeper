#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Functions_inc.h"
#include "Macros.h"
#include "MyPrint.h"
#include "Structs.h"
/* struct members for the Cell*/

//My FunctionS' Purpose
//void make_board(Board*); /* pointer to the board in order to create board */
//void print_board(Board*); /* pointer to the board and printing board */
//void bombplacing_randomly(Board*, int); /* pointer to the board and number of bombs  */
//void numof_adjacent_mines(Board*); /* pointer to the board and determining number of bombs in adjacency cells */
//void uncover(Board*, int, int); /* pointer to the board and selected coordinates by the user for uncovering cells */
//void reveal_automatically(Board*, int, int); /* pointer to the board and cell's coordinates for automatic reveal of cells */
//void check_for_win(Board*, int); /* pointer to the board and number of mines  */
//void play_game(); /* function to play the game */

int Flagcounnt;

/* Global variables before starting game,assigning false to them*/
bool lose = false;
bool win = false;
void make_board(Board * ptr)
{
    int i, j;
    ptr->cells = (Cell**)malloc((ptr->height + 2) * sizeof(Cell*)); /* array of pointers*/

    for (i = 0; i <= ptr->height + 1; ++i)
        ptr->cells[i] = (Cell*)malloc((ptr->width + 2) * sizeof(Cell)); /* dynamic 2 dimensional array of cells and creating cells in board*/
    for (i = 0; i <= ptr->height + 1; ++i) {
        for (j = 0; j <= ptr->width + 1; ++j) {
            if (i == 0 || i == ptr->height + 1 || j == 0 || j == ptr->width + 1)
            {
                ptr->cells[i][j].bomb = false;
                ptr->cells[i][j].uncovered = true;
            }

            else
            {
                ptr->cells[i][j].ch ='-';  // making cells with character '-'
                ptr->cells[i][j].number_of_mines = 0; // before the game it is zero
                ptr->cells[i][j].bomb = false; // there is no bomb before the game
                ptr->cells[i][j].uncovered = false;
            }
        }
    }

    return;
}

void print_board(Board * ptr)
{
    system("cls"); // clearing the screen

    printf("   ");
    int i, j;
    for (i = 1; i <= ptr->width; ++i){ /* loop in order print each row */
       if(i<10) printf("%d ", i); // numbers which shows rows
       else printf("%d", i);
    }
    printf("\n");
    /* nested loop in order to print numbers for columns and characters for cells */
    for (i = 1; i <= ptr->height; ++i) {
        for (j = 0; j <= ptr->width; ++j) {
            if (j == 0 && i<10) printf("%d  ", i);   // number which shows columns
            else if (j == 0 && i > 9) printf("%d ", i);
            else {
                if (ptr->cells[i][j].ch == '!') printf(flag);
                    
                else if (ptr->cells[i][j].ch == '*') printf(Bomb);
                    
                else if(ptr->cells[i][j].ch == '-') printf(Orange_sqr);
                else  printf("%c ", ptr->cells[i][j].ch);
            }

        } //printf("%c ", ptr->cells[i][j].ch); // printing cells in the board
         printf("\n");
        }
        return;
}
 

void bombplacing_randomly(Board * ptr, int mines)
{
    int random_row, random_col, num_of_mine = 0;
    while (num_of_mine < mines)
    {
        random_row = rand() % ptr->height + 1; // generating random number
        random_col = rand() % ptr->width + 1;  // generating random number


        if (ptr->cells[random_row][random_col].bomb == false && (random_row != 0 && random_col != 0)) // checking for numbers which were generated before or not
        {
            ptr->cells[random_row][random_col].bomb = true; // if not, make a new bomb
            num_of_mine++;
        }
    }
    if(ptr->height==9 && ptr->width==9) checkminelimit(ptr, mines);
     
    return;
}
//checks the mine limit in each row cant be bigger than 3
void checkminelimit(Board* ptr, int mines) {
    int i, j,c=0;
    for (j = 1; j <= ptr->height; ++j) {
        for (i = 0; i <= ptr->width; ++i) {
            if (ptr->cells[i][j].ch == '*')
                c++;
        }
        if (c == 4) bombplacing_randomly(ptr, mines);
    }

}
void numof_adjacent_mines(Board * ptr)
{
    /*
    Count all the mines in the 8 adjacentmines
        cells
      (i-1,j-1)  (i-1,j) (i-1,j+1)
              \    |    /
               \   |   /
        (i,j-1)---CELL---(i,j+1)
                 / |  \
               /   |    \
       (i+1,j-1) (i+1,j) (i+1,j+1)
    */

    int i, j, m, n;
    for (i = 1; i <= ptr->height; ++i) {
        for (j = 1; j <= ptr->width; ++j) {
            if (ptr->cells[i][j].bomb == false) {
                for (m = i - 1; m <= i + 1; ++m)
                    for (n = j - 1; n <= j + 1; ++n)
                        if (ptr->cells[m][n].bomb == true) // checking number of bombs in adjacent cell
                            ptr->cells[i][j].number_of_mines++;
            }
        }
    }
    return;
}

void uncover(Board * ptr, int a, int b)
{
    if (ptr->cells[a][b].bomb == true)
    {
        lose = true; // terminate the game "in the play game function (while loop)"
        int i, j;
        /* nested loop to uncover cells */
        for (i = 1; i <= ptr->height; ++i)
            for (j = 1; j <= ptr->width; ++j)
                if (ptr->cells[i][j].bomb == true) /* if there is a bomb */
                    ptr->cells[i][j].ch = '*'; // showing all bombs
                else
                    ptr->cells[i][j].ch = ptr->cells[i][j].number_of_mines + '0'; // putting number of mines in surrounding cells
        print_board(ptr);
        printf("\n\033[0;31m");
        int nLagg = 30;
        printf(BMagenta);
        printf("                                                                                       \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("__     ______  _    _   _      ____   _____ ______ \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf(" \\ \\   / / __ \\| |  | | | |    / __ \\ / ____|  ____|\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("  \\ \\_/ / |  | | |  | | | |   | |  | | (___ | |__   \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("   \\   /| |  | | |  | | | |   | |  | |\\___ \\|  __|  \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    | | | |__| | |__| | | |___| |__| |____) | |____ \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    |_|  \\____/ \\____/  |______\\____/|_____/|______|\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif

        printf("\n\033[0;31m");
        printf("  ________                        ________                    ._.\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("  /  _____/_____    _____   ____   \\_____  \\___  __ ___________| |\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf(" /   \\  ___\\__  \\  /     \\_/ __ \\   /   |   \\  \\/ // __ \\_  __ \\ |\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf(" \\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  /    |    \\   /\\  ___/|  | \\/\\|\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("  \\______  (____  /__|_|  /\\___  > \\_______  /\\_/  \\___  >__|   __\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("         \\/     \\/      \\/     \\/          \\/          \\/       \\/\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        gotoxy(1, 50);
        system("pause");
        system("cls");
        return;
    }

    ptr->cells[a][b].ch = ptr->cells[a][b].number_of_mines + '0'; //  showing number of bombs in the cell
    if (ptr->cells[a][b].number_of_mines == 0 && ptr->cells[a][b].ch != '!')
        reveal_automatically(ptr, a, b); // if number of bomb is 0 in cell then reveal automatically
    else
        ptr->cells[a][b].uncovered = true;

    return;
}

void reveal_automatically(Board * ptr, int a, int b)
{
    int i, j;

    if (ptr->cells[a][b].uncovered == false)
    {
        ptr->cells[a][b].uncovered = true;
        /* nested loop to reveal automatically */
        for (i = a - 1; i <= a + 1; ++i)
            for (j = b - 1; j <= b + 1; ++j)
                if (ptr->cells[i][j].uncovered == false)
                    uncover(ptr, i, j); //calling function in order to uncover cells
    }
    return;
}

void check_for_win(Board * ptr, int mines)
{
    int i, j, counter = 0; /* number of cells without bombs. At first assigning to zero*/


    for (i = 1; i <= ptr->height; ++i)
        for (j = 1; j <= ptr->width; ++j)
            if (ptr->cells[i][j].bomb == false && ptr->cells[i][j].ch != '-' && ptr->cells[i][j].ch != '!') /*if no bomb. increment*/
                counter++; /* incrementing cells */

         /* if counter equal below equation, it means user found all the cells which does not contain mines*/
    if (counter == (ptr->height * ptr->width) - mines)
    {
        win = true;
        for (i = 1; i <= ptr->height; ++i)
            for (j = 1; j <= ptr->width; ++j)
                if (ptr->cells[i][j].bomb == true) /* if there is a bomb */
                    ptr->cells[i][j].ch = ' * '; // show all the bombs
                else
                    ptr->cells[i][j].ch = ptr->cells[i][j].number_of_mines + '0'; // showing numbers in the cells

        print_board(ptr);
        printf(BRed "Please Press Any key to Continue!" RESET);
        getch();
        system("cls");

        int nLagg = 30;
        printf(BBlue);
        printf("                                                                                       \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                   YYYYYYY       YYYYYYY     OOOOOOOOO     UUUUUUUU     UUUUUUUU\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                   Y:::::Y       Y:::::Y   OO:::::::::OO   U::::::U     U::::::U\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                   Y:::::Y       Y:::::Y OO:::::::::::::OO U::::::U     U::::::U\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                   Y::::::Y     Y::::::YO:::::::OOO:::::::OUU:::::U     U:::::UU\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                   YYY:::::Y   Y:::::YYYO::::::O   O::::::O U:::::U     U:::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                      Y:::::Y Y:::::Y   O:::::O     O:::::O U:::::D     D:::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                       Y:::::Y:::::Y    O:::::O     O:::::O U:::::D     D:::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                        Y:::::::::Y     O:::::O     O:::::O U:::::D     D:::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                         Y:::::::Y      O:::::O     O:::::O U:::::D     D:::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                          Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                          Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                          Y:::::Y       O::::::O   O::::::O U::::::U   U::::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                          Y:::::Y       O:::::::OOO:::::::O U:::::::UUU:::::::U \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                       YYYY:::::YYYY     OO:::::::::::::OO   UU:::::::::::::UU  \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                       Y:::::::::::Y       OO:::::::::OO       UU:::::::::UU    \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                       YYYYYYYYYYYYY         OOOOOOOOO           UUUUUUUUU          \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                                                                                 \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    WWWWWWWW                           WWWWWWWWIIIIIIIIIINNNNNNNN        NNNNNNNN      !!!  !!! \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    W::::::W                           W::::::WI::::::::IN:::::::N       N::::::N     !!:!!!!:!!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    W::::::W                           W::::::WI::::::::IN::::::::N      N::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    W::::::W                           W::::::WII::::::IIN:::::::::N     N::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("     W:::::W           WWWWW           W:::::W   I::::I  N::::::::::N    N::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("      W:::::W         W:::::W         W:::::W    I::::I  N:::::::::::N   N::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("       W:::::W       W:::::::W       W:::::W     I::::I  N:::::::N::::N  N::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("        W:::::W     W:::::::::W     W:::::W      I::::I  N::::::N N::::N N::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("         W:::::W   W:::::W:::::W   W:::::W       I::::I  N::::::N  N::::N:::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("          W:::::W W:::::W W:::::W W:::::W        I::::I  N::::::N   N:::::::::::N     !:::!!:::!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("           W:::::W:::::W   W:::::W:::::W         I::::I  N::::::N    N::::::::::N     !!:!!!!:!!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("            W:::::::::W     W:::::::::W          I::::I  N::::::N     N:::::::::N      !!!  !!! \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("             W:::::::W       W:::::::W         II::::::IIN::::::N      N::::::::N               \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("              W:::::W         W:::::W          I::::::::IN::::::N       N:::::::N      !!!  !!! \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("               W:::W           W:::W           I::::::::IN::::::N        N::::::N     !!:!!!!:!!\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("                WWW             WWW            IIIIIIIIIINNNNNNNN         NNNNNNN      !!!  !!! \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif

        //printf("\n\nPress any key --> ");
        gotoxy(1, 50);
        system("pause");
        system("cls");

        return;
    }
}

void play_game()
{
revet:
    srand(time(NULL)); // set seed for rand() in the "bombplacing_randomly" function

    int x, y, row, column, mines;
    char op;
    gotoxy(95, 25);
    printf(F_YELLOW "Please enter the size of board(X*Y): ");
    gotoxy(132, 25);
    scanf("%d%d", &x, &y);
    while (getchar() != '\n');
    gotoxy(95, 26);
    printf(F_YELLOW "Please enter the number of mines: ");
    gotoxy(129, 26);
    scanf("%d", &mines);
    while (getchar() != '\n');
    if (x < 1 || y < 1 ){
        while (getchar() != '\n');
        system("cls");
        gotoxy(95, 28);
        printf("\x1b[31mPlease Enter a valid numbers!" RESET);
        Sleep(2500);
        system("cls");
        goto revet;
    }
    Board* ptr = (Board*)malloc(sizeof(Board)); /* creating dynamic array */
    ptr->height = x;
    ptr->width = y;

    make_board(ptr);
    bombplacing_randomly(ptr, mines);
    Flagcounnt = mines;
    numof_adjacent_mines(ptr);

req: do
    {
       printf(BCyan);
       print_board(ptr);
       printf(F_PINK "Flags = %d\n" RESET, Flagcounnt);
        printf("Would you like to Open or Flag?  'O' or 'F' ");
        /*scanf(" %c", &op);*/
        op = getchar();
        while (getchar() != '\n' && op != '\n');
        fflush(stdin); // clearing buffer
            printf(BMagenta "Enter the row number: ");
            scanf("%d", &row);
            while (getchar() != '\n');
            printf(BMagenta "Enter the column number: ");
            scanf("%d", &column);
            while (getchar() != '\n');
    
            if ((row <0 && row > x + 1 && row == EOF && row == '\n') || (column > y + 1 && column < 0 && column == EOF && column == '\n')  || (op != EOF && op == '\n' || op == '!' || op == '_' || op == '*'))
                while (getchar() != '\n');
            else if (row > 0 && column > 0 && row < x + 1 && column < y + 1 && row != EOF && row != '\n' && column != EOF && column != '\n' && op != EOF && op != '\n' || (op == 'O' || op == 'o' || op == 'F' || op == 'f')) {
            if (op == 'O' || op == 'o') /* O -> Open */
                uncover(ptr, row, column);
            else if (op == 'F' || op == 'f') { /* F -> Flag*/
                if (ptr->cells[row][column].ch == '!') {
                    ptr->cells[row][column].ch = '-';
                    Flagcounnt++;
                }

                else if (row > 0 && column > 0 && row < x + 1 && column < y + 1 && Flagcounnt>0 ) {
                    ptr->cells[row][column].ch = '!';
                    Flagcounnt--;
                }
            }
            else if (op == 'X' && row==1 && column==1)
                cheat(ptr,row,column);
        }
        else  while (getchar() != '\n');
        if (!lose) check_for_win(ptr, mines);
    } while (!lose && !win);

    /* memory releasing */
    for (int i = 0; i <= ptr->height + 1; ++i)
        free(ptr->cells[i]); /* free each cell */
    free(ptr->cells); /* free array of pointers */
    return;
}

void cheat (Board* ptr, int a , int b) {
    if (a==1&& b==1)
    {
        lose = true; // terminate the game "in the play game function (while loop)"
        int i, j;
        /* nested loop to uncover cells */
        for (i = 1; i <= ptr->height; ++i)
            for (j = 1; j <= ptr->width; ++j)
                if (ptr->cells[i][j].bomb == true) /* if there is a bomb */
                    ptr->cells[i][j].ch = '*'; // showing all bombs
                else
                    ptr->cells[i][j].ch = ptr->cells[i][j].number_of_mines + '0'; // putting number of mines in surrounding cells
        print_board(ptr);
        printf("\n\033[0;31m");
        int nLagg = 30;
        printf(BMagenta);
        printf("                                                                                       \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("__     ______  _    _   _      ____   _____ ______ \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf(" \\ \\   / / __ \\| |  | | | |    / __ \\ / ____|  ____|\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("  \\ \\_/ / |  | | |  | | | |   | |  | | (___ | |__   \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("   \\   /| |  | | |  | | | |   | |  | |\\___ \\|  __|  \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    | | | |__| | |__| | | |___| |__| |____) | |____ \n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("    |_|  \\____/ \\____/  |______\\____/|_____/|______|\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif

        printf("\n\033[0;31m");
        printf("  ________                        ________                    ._.\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf("  /  _____/_____    _____   ____   \\_____  \\___  __ ___________| |\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
        printf(" /   \\  ___\\__  \\  /     \\_/ __ \\   /   |   \\  \\/ // __ \\_  __ \\ |\n");
#ifdef _WIN32
        Sleep(nLagg);
#else
        usleep(nLagg * 100);
#endif
            printf(" \\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  /    |    \\   /\\  ___/|  | \\/\\|\n");
#ifdef _WIN32
            Sleep(nLagg);
#else
            usleep(nLagg * 100);
#endif
            printf("  \\______  (____  /__|_|  /\\___  > \\_______  /\\_/  \\___  >__|   __\n");
#ifdef _WIN32
            Sleep(nLagg);
#else
            usleep(nLagg * 100);
#endif
            printf("         \\/     \\/      \\/     \\/          \\/          \\/       \\/\n");
#ifdef _WIN32
            Sleep(nLagg);
#else
            usleep(nLagg * 100);
#endif
        gotoxy(1, 50);
        system("pause");
        system("cls");

        return;
    }

    ptr->cells[a][b].ch = ptr->cells[a][b].number_of_mines + '0'; //  showing number of bombs in the cell
    if (ptr->cells[a][b].number_of_mines == 0 && ptr->cells[a][b].ch != '!')
        reveal_automatically(ptr, a, b); // if number of bomb is 0 in cell then reveal automatically
    else
        ptr->cells[a][b].uncovered = true;

    return;
}


int Logic()
{
    clock_t begin = clock(); /* getting time at the beginning */

    play_game();

    clock_t end = clock();  /* getting time at the end */
    double spend_time = (double)(end - begin) / CLOCKS_PER_SEC; /* time difference */
    char choice;
    gotoxy(88, 25);
    printf(BGreen);
    printf("You spent %.2f seconds playing the game\n", spend_time);
    gotoxy(95, 29);
    printf(BCyan);
        printf("Do you want to play again?");
        gotoxy(95, 30);
        printf(BYellow);
        printf("Press Y or N : ");
        choice = getchar();
        while (choice != '\n' && getchar() != '\n') {};
        if (choice == 'Y' || choice == 'y') {
            lose = false;
            win = false;
            system("cls");
            Logic();
        }
        else if (choice == 'N' || choice == 'n') {
            system("cls");
            gotoxy(95, 28);
            printf(BYellow "Have Fun!!!" RESET);
            _Exit(0);
        }
        else if (choice == 0 || choice == EOF || choice == '\n' || choice > 10 || choice < 0) {
            while (getchar() != '\n');
            system("cls");
            gotoxy(95, 28);
            printf("\x1b[31mPlease Enter a valid number!");
            Sleep(2000);
            system("cls");
            newgame();
        }
    
    return 0;
}
