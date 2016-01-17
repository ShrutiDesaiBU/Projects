import java.util.*;

public class JavaSolver 	
{  
//Check free space is available 	
	static int isAvailable(int puzzle[][], int row, int col, int num)
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
	static int  fillSudoku(int puzzle[][], int row, int col)
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
	                if((isAvailable(puzzle,row,col,i+1))==1)
	                {
	                    puzzle[row][col] = i+1;
	                    if((col+1)<16)
	                    {
	                        if((fillSudoku(puzzle, row, col +1))==1) 
				return 1;
	                        else puzzle[row][col] = 0;
	                    }
	                    else if((row+1)<16)
	                    {
	                        if((fillSudoku(puzzle, row+1, 0))==1) 
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
	//Function called in Java file
	public  static String solve_java(String inputStr)
	{ 
		char char_input_Array[]=new char[256];
	     //System.out.println("String is "+inputStr);
		char_input_Array = inputStr.toCharArray();
		
		//Convert to int array
		int i,j;
		int puzzle[][]=new int[16][16];
		int count=0;
		int input_intArray[]=new int[256];
		for(i=0;i<256;i++)
		{
			if(char_input_Array[i]==46)
			{
				input_intArray[i]=0;
			}
			else if(char_input_Array[i]<60 
			&& char_input_Array[i]!=46)
			{
				input_intArray[i]=(char_input_Array[i]-47);
			}
			else if(char_input_Array[i]>60)
			{
				input_intArray[i]=(char_input_Array[i]-54);
			}
		}
	//Additional

		for(i=0;i<16;i++)
		{
		for(j=0;j<16;j++)
		{
		puzzle[i][j]=input_intArray[count++];	
		}
		}
	fillSudoku(puzzle,0,0);
	//System.out.println("Output:");
	int cnter=0;
	int output_intArr[]=new int[256];
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
		output_intArr[cnter++]=puzzle[i][j];
		}
	}
	char output_charArr[]=new char[256];
	for(i=0;i<256;i++)
	{
	if(1<=output_intArr[i] && output_intArr[i]<=10)
		{output_charArr[i]=(char)(output_intArr[i]+47);}
	else if(11<=output_intArr[i] && output_intArr[i]<=16)
		{output_charArr[i]=(char)(output_intArr[i]+54);}
	}
	char puzzle_soln[][]=new char[16][16];
	//System.out.println("Final Ouput in JAva");
	int cn=0;
	/*for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
		puzzle_soln[i][j]=output_charArr[cn++];
		System.out.print(puzzle_soln[i][j]+" ");
		}
		System.out.println();
	} */
	
		String b=new String(output_charArr);
		return b;
		
	}
}
	    

