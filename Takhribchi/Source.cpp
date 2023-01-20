/*Simplicity, carried to the extreme, becomes elegance.*/
//In order for this program to run corretly , please set your console window to fullscreen by pressing F11 while it is open.
// please enable UTF-8 Support on your system (Control Panel > Clock and Region > Region > Administrative tab > Change system locale button > enable Beta:Use Unicode UTF-8 for worldwide language support)
//_____________________________________________
//Fullscreen console (1920*1080) size:
//total cols = 209
//total rows = 56
//_____________________________________________

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <WinUser.h>
#include "MyPrint.h"
#include "RWFile.h"
#include "Functions_inc.h"
#pragma warning (disable:4996)
#pragma comment(lib, "Winmm.lib")

int main() {
	system("cls");
    char ch;
	printwlc(); system("cls");
	profile(); system("cls");
	newgame();
    getch();
	return 0;
}
