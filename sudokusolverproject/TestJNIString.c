#include <jni.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "SudokuSolver.h"
//Check free space is available
int isAvailable(int puzzle[][16], int row, int col, int num)
{
    int rowStart = (row/4) * 4;
    int colStart = (col/4) * 4;
    int i, j;
    for(i=0; i<16; ++i)
    {
        if (puzzle[row][i] == num) return 0;
        if (puzzle[i][col] == num) return 0;
        if (puzzle[rowStart + (i%4)][colStart + (i/4)] == num) return 0;
    }
    return 1;
}
//fill correct value at unalocated location
int fillSudoku(int puzzle[][16], int row, int col)
{
    int i;
    if(row<16 && col<16)
    {
        if(puzzle[row][col] != 0)
        {
            if((col+1)<16) return fillSudoku(puzzle, row, col+1);
            else if((row+1)<16) return fillSudoku(puzzle, row+1, 0);
            else return 1;
        }
        else
        {
            for(i=0; i<16; ++i)
            {
                if(isAvailable(puzzle,row,col,i+1))
                {
                    puzzle[row][col] = i+1;
                    if((col+1)<16)
                    {
                        if(fillSudoku(puzzle, row, col +1)) 
			return 1;
                        else puzzle[row][col] = 0;
                    }
                    else if((row+1)<16)
                    {
                        if(fillSudoku(puzzle, row+1, 0)) 
			return 1;
                        else puzzle[row][col] = 0;
                    }
                    else return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}
//Caller functon for sudoku to get solved
char* call_Func(const char *array)
{
int i,j;
int puzzle[16][16];
int count=0;
int input_intArray[256];
for(i=0;i<256;i++)
{
	if(array[i]==46)
	{
		input_intArray[i]=0;
	}
	else if(array[i]<60 && array[i]!=46)
	{
		input_intArray[i]=(array[i]-47);
	}
	else if(array[i]>60)
	{
		input_intArray[i]=(array[i]-54);
	}
}
for(i=0;i<16;i++)
{
	for(j=0;j<16;j++)
	{
	puzzle[i][j]=input_intArray[count++];	
	}
}
fillSudoku(puzzle,0,0);
int cnter=0;
int output_intArr[256];
for(i=0;i<16;i++)
{
	for(j=0;j<16;j++)
	{
	output_intArr[cnter++]=puzzle[i][j];
	}
}
char *output_charArr=malloc(sizeof(char)*256);;
for(i=0;i<256;i++)
{
if(1<=output_intArr[i] && output_intArr[i]<=10)
	{output_charArr[i]=(output_intArr[i]+47);}
else if(11<=output_intArr[i]<=16)
	{output_charArr[i]=output_intArr[i]+54;}
}
char puzzle_soln[16][16];
//printf("\nFinal Ouput in C\n");
int cn=0;

return output_charArr;
}
//JNI Calling function from Java Driver part

JNIEXPORT jstring JNICALL Java_SudokuSolver_solve_1c
  (JNIEnv *env, jobject thisObj, jstring inJNIStr)
{
   // Step 1: Convert the JNI String (jstring) into C-String (char*)
   const char *inCStr = (*env)->GetStringUTFChars(env, inJNIStr, NULL);
   if (NULL == inCStr) return NULL;
   // Step 2: Perform its intended operations
   //printf("In C, the received string is: %s\n", inCStr);
   char *output_String=call_Func(inCStr);
   // Step 3: Convert the C-string (char*) into JNI String (jstring) and return
   return (*env)->NewStringUTF(env,output_String);
}
