//Convert input string to char array
function createArray(length) {
    var arr = new Array(length || 0),
        i = length;

    if (arguments.length > 1) {
        var args = Array.prototype.slice.call(arguments, 1);
        while(i--) arr[length-1 - i] = createArray.apply(this, args);
    }

    return arr;
}
//To check if unallocated space is available
function isAvailable(puzzle, row, col, num)
{
    var rowStart = Math.floor(row/4) * 4;
    var colStart = Math.floor(col/4) * 4;
    var i, j;
    for(i=0; i<16; ++i)
    {
        if (puzzle[row][i] == num) return 0;
        if (puzzle[i][col] == num) return 0;
        //console.log(colStart + Math.floor(i/4));
        if (puzzle[rowStart + Math.floor(i%4)][Math.ceil(colStart + Math.floor(i/4))] == num) return 0;
    }
    return 1;
} 
//To fill unallocated space with correct value
function fillSudoku(puzzle, row, col)
{
    var i;
    if(row<16 && col<16)
    {
        if(puzzle[row][col] != 0)
        {
            if((col+1)<16) 
            	return fillSudoku(puzzle, row, col+1);
            else if((row+1)<16) 
            	return fillSudoku(puzzle, row+1, 0);
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
//Javascript sudoku solver function
function solve_JS(inputStr)
{ 
	
    //document.write("String is "+ inputStr);
	char_input_Array = inputStr.split("");
	
	//Convert to int array
	var i,j;
	var puzzle = createArray(16,16);
	var count=0;
	var input_intArray = new Array(256);
	for(i=0;i<256;i++)
	{
		if(char_input_Array[i].charCodeAt()==46)
		{
			//console.log(i);
			input_intArray[i]=0;
		}
		else if(char_input_Array[i].charCodeAt()<60 && 
		char_input_Array[i].charCodeAt()!=46)
		{
			input_intArray[i]=(char_input_Array[i].charCodeAt()-47);
		}
		else if(char_input_Array[i].charCodeAt()>60)
		{
			input_intArray[i]=(char_input_Array[i].charCodeAt()-54);
		}
	}

	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			puzzle[i][j]=input_intArray[count++];
			//document.write(puzzle[i][j]);	
		}

	}

	fillSudoku(puzzle,0,0);

	
	var cnter=0;
	var output_intArr=new Array(256);
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			output_intArr[cnter++]=puzzle[i][j];
		}
	}
	for(i=0;i<256;i++)
	//document.write(output_intArr[i]);
	var output_charArr=new Array(256);
	for(i=0;i<256;i++)
	{
		if(1<=output_intArr[i] && output_intArr[i]<=10)
			{output_charArr[i]=String.fromCharCode(output_intArr[i]+47);}
		else if(11<=output_intArr[i] && output_intArr[i]<=16)
			{output_charArr[i]=String.fromCharCode(output_intArr[i]+54);}
	}

	var puzzle_soln = createArray(16,16);
	//document.write("Final Ouput");
	var cn=0;
	var outputString;
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			puzzle_soln[i][j]=output_charArr[cn++];
			//print(puzzle_soln[i][j]);
			//document.write(puzzle_soln[i][j]+" ");
			outputString = output_charArr.toString();
		var replaced = outputString.split(',').join('');		
		}
		
		//document.write();
	}
	return replaced;
}



