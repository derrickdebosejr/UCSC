import java.io.*;
import java.util.*;

public class FileReverse {
	//static File inFile = new File("gettysburg.txt");for testing puropses
	//static File outFile = new File("out.txt");
	public static void main (String[] args) throws IOException{
		if(args.length< 2) {
			System.out.println("Usage: java -jar FileReverse.jar <input file> <output file>");
			System.exit(1);
		}
		File inFile = new File(args[0]);
		
		Scanner in = new Scanner(inFile);//reads in arguments
		PrintWriter out = new PrintWriter(args[1]);
		
		while(in.hasNextLine()) {
			String line = in.nextLine().trim() + " ";
			String [] token = line.split("\\s+");
			int totalString = token.length;
			for(int i=0; i< totalString; i++) {
				out.println(stringReverse(token[i]));
			}
		}
		in.close();
		out.close();
	}
	public static String stringReverse (String s) {
    		int counter=0;
    		char[] temps= new char[s.length()];
        	char[] c = s.toCharArray();
        	for( int i=c.length-1; i>=0; i--){
       			temps[counter] = c[i];
       			counter++;
        	}
        	return String.valueOf(temps);
	}
}
