#pragma once
#include "Structs.h"
#pragma warning (disable:4996)
// opens a file and write the inpput to it
void WritetomyFile(char x[]) {
	// Pointer to file
	FILE* log;
	
	// Name of the file
	// and mode of the file
	log = fopen("C:\\Users\\Kebabist\\source\\repos\\Takhribchi\\UserProfiles.txt", "w");
	/*struct Login l;*/
	/*fwrite(&x, sizeof(x), 1, log);*/
	fputs(x, log);
	fclose(log);
}
void readfile(char filename[])
{
	FILE* fptr;

	char c;

	/*printf("Enter the filename to open \n");
	scanf("%s", filename);*/

	// Open file
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}

	// Read contents from file
	c = fgetc(fptr);
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fptr);
	}
	fclose(fptr);
}




//void writeindex(int x) {
//	// Pointer to file
//	FILE* index;
//
//	// Name of the file
//	// and mode of the file
//	index = fopen("C:\\Users\\Kebabist\\source\\repos\\Takhribchi\\index.txt", "wt");
//	fwrite(&x, sizeof(x), 1, index);
//	fclose(index);
//}

//int readindex() {
//	FILE* f = fopen("C:\\Users\\Kebabist\\source\\repos\\Takhribchi\\index.txt", "r");
//	int i;
//	char buf[10];
//	for (i = 0; i != 11; i++) {
//		fgets(buf, 10, f);
//	}
//	fscanf(f, "%d", &i);
//	return i;
//}
