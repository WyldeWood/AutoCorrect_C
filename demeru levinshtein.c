// demeru levinshtein.cpp : Defines the entry point for the console application.
// if 1st and 2nd match 1st and 2nd match on other row cost is 1, substitutuin
#include <stdlib.h>
#define _CRTDBG_MAP_ALLOC
#include <string.h>
#include <crtdbg.h>


// signature declarations
int FindLeast(int a, int b, int c, int d);
int ComputeEditDistance(const char* String1, const char* String2);

int FindLeast(int a, int b, int c, int d) {
	int least = a;

	if (b < least) {
		least = b;
	}
	if (c < least) {
		least = c;
	}
	if (b < least){ 
		least = b;
	}
	return least;
}

int ComputeEditDistance(const char* String1, const char* String2) {
	const int String1Length = strlen(String1);
	const int String2Length = strlen(String2);
	int String1LengthForMatrix = String1Length + 1;
	int String2LengthForMatrix = String2Length + 1;
	 
	int ** matrix = (int**)malloc(sizeof(int*)*String1LengthForMatrix);//malloc array of arrays
	for (int i = 0; i < String1LengthForMatrix; i++){
	  matrix[i] = (int*)malloc(sizeof(int)*String2LengthForMatrix);
	}

	for (int i = 0; i < String1LengthForMatrix; i++) { //initialize matrix to 0's
		for (int j = 0; j < String2LengthForMatrix; j++) {
			matrix[i][j] = 0;
		}
	}
	int SubstitutionCost;
	for (int i = 1; i < String1LengthForMatrix; i++) {// number the top row and left column 1 - length of string
		matrix[i][0] = i;
	}
	for (int j = 1; j < String2LengthForMatrix; j++) {// number the top row and left column 1 - length of string
		matrix[0][j] = j;	
	}
	int least;
	for (int i = 1; i < String1LengthForMatrix; i++) {
		for (int j = 1; j < String2LengthForMatrix; j++) {// number the top row and left column 1 - length of string
			
			if (String1[i-1] == String2[j-1]) {
				SubstitutionCost = 0;
			}
			else {
				SubstitutionCost = 1;
			}
			if (i > 1 && j > 1 && (String1[i - 1] == String2[j - 2]) && (String1[i - 2] == String2[j - 1])) {
				least = FindLeast(matrix[i - 2][j - 2]+1, matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + SubstitutionCost);
			}
			else {
				least = FindLeast(9999,matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + SubstitutionCost);
			}	
			matrix[i][j] = least;		
		}
	}
	int editDistance = matrix[String1LengthForMatrix - 1][String2LengthForMatrix - 1];

	for (int i = 0; i < String1LengthForMatrix; i++) {//print matrix
		for (int j = 0; j < String2LengthForMatrix; j++) {
		}
	}
	// printf("length of string 1 + 1 = %d", String1LengthForMatrix);
	for (int i = 0; i < String1LengthForMatrix; i++) {
		free(matrix[i]);
	}
	free(matrix);
	_CrtDumpMemoryLeaks();
	return(editDistance);
}


	 