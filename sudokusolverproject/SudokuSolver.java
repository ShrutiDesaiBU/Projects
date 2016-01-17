import java.io.*;
import java.util.Scanner;
import java.io.File;
import java.lang.*;
import javax.script.*;
import java.io.Reader;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.concurrent.TimeUnit;
import java.text.DecimalFormat;

public class SudokuSolver
{
static 
{
System.loadLibrary("myjni"); // libmyjni.so
}
private native String solve_c(String input);//native function


 public static void main(String [] args) throws IOException,ScriptException,Exception
 {
	SudokuSolver fileObj = new SudokuSolver();
    	String line = null;
	String lang1 = null;
	int i;
	String strC="c";
	String strJS = "javascript";
	String strJ = "java";
	String strPy="python";
	String strPr="prolog";
	String output = null;
  	String[] input_str ;
	String solved_java_string=null;
	String solved_c_string=null;
	String solved_js_string = null;
	String outputString_frm_file = null;
	String timeTakenInSec = null ;
	String solved_python_string = null;
	
	long startTime, endTime;
	double	timeDiff;
	float check;
        // This will reference one line at a time
	if(args.length > 0) 
	{
		lang1 = args[0];
		String[] parts = lang1.split("=");
		String part1 = parts[0];
		String part2 = parts[1];
	   
		File file = new File(args[3]);
		Scanner sc = new Scanner (file);	
      		{
		line = sc.nextLine();
            	input_str = line.split("\n");
				
            	
      		    String input_String=input_str[0];
				
		if (part2.equals(strJ))
		{	startTime = System.nanoTime();
			
			solved_java_string = 
			JavaSolver.solve_java(input_String);
			endTime = System.nanoTime();
			timeDiff = (endTime - startTime)/1000000000.0;
			timeTakenInSec = String.format("%.3f", timeDiff);
			
			outputString_frm_file = solved_java_string + "\n"
		 + "Time Taken = " + timeTakenInSec + "seconds" ;
			
		}	
	   	else if (part2.equals(strC))
		{
			startTime = System.nanoTime();
			
			String output_c=new SudokuSolver().
			solve_c(input_String);
			solved_c_string=output_c;
			
			endTime = System.nanoTime();
			timeDiff = (endTime - startTime)/1000000000.0;
			timeTakenInSec = String.format("%.3f", timeDiff);
			outputString_frm_file = solved_c_string + "\n" +
			 "Time Taken = " + timeTakenInSec +"seconds" ;
			
		}
		else if (part2.equals(strJS))
		{
		startTime = System.nanoTime();
		ScriptEngineManager manager = new ScriptEngineManager();
		ScriptEngine engine = manager.getEngineByName("JavaScript");
		// read script file
		engine.eval(Files.newBufferedReader(Paths.get("/import/linux/home/sdesai4/PROJECTPL/sudosolve.js"), StandardCharsets.UTF_8));
		Invocable inv = (Invocable) engine;
		// call function from script file
		solved_js_string = (String)inv.invokeFunction("solve_JS", input_String);   
		endTime = System.nanoTime();
		timeDiff = (endTime - startTime)/1000000000.0;
		timeTakenInSec = String.format("%.3f", timeDiff);
		outputString_frm_file = solved_js_string + "\n" +  
		"Time Taken = " + timeTakenInSec + "seconds" ;
		
		
		}
		else if (part2.equals(strPy)){
					startTime = System.nanoTime();
			
			ProcessBuilder pb = new ProcessBuilder("/usr/bin/python", "/import/linux/home/pdhanaw1/with4/sudoku_solver.py",input_String);
			pb.redirectErrorStream(true);
		        try {
		            Process p = pb.start();
			BufferedWriter out = new BufferedWriter
			(new OutputStreamWriter(p.getOutputStream()) );

					out.flush();
			Reader reader = 
			new InputStreamReader(p.getInputStream());
					int ch;
					String str_out = "";
					while ((ch = reader.read()) != -1) {
					str_out = str_out + (char) ch ;
					solved_python_string = str_out;
					}
		            reader.close();
					} catch (Exception ex) {
		            ex.printStackTrace();
				}
			endTime = System.nanoTime();
			timeDiff = (endTime - startTime)/1000000000.0;
			timeTakenInSec = String.format("%.3f", timeDiff);

			outputString_frm_file = solved_python_string + "\n" + "Time Taken = " + timeTakenInSec + "seconds" ;
			}
		 	
        sc.close();
        }
        File outFile = new File(args[2]);
        FileWriter fWriter = new FileWriter(outFile, true);
        PrintWriter pWriter = new PrintWriter(fWriter);
        pWriter.println(outputString_frm_file);
        pWriter.close();
     }
}

}
