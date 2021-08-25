import java.io.*;
import java.util.*;

public class Balanced {
	public static void main(String args[]) throws IOException {
		if(args.length< 2) {
			System.out.println("Usage: java -jar ChessBoard.jar <input file> <output file>");
			System.exit(1);
		}		
		File inFile = new File(args[0]);
        File outFile = new File(args[1]);
		Scanner in = new Scanner(inFile);//reads in arguments
		PrintWriter out = new PrintWriter(outFile);//prints into the out.txt file
		
		while (in.hasNextLine()) {
			RefStack stack = new RefStack();
			int pushCounter=0;//Counts how many times push occurs
			int popCounter=0;//Counts how many times pop occurs
			boolean isEven = true;//A check to make sure every close brace is even with an open brace
			String line = in.nextLine();//Input in string
			char[] c = line.toCharArray();//Convert that string to a Char array
			for(int i=0;i<c.length; i++) {//go through full char array
				if(c[i]=='(') {
					pushCounter++;//add to counter
					stack.push(c[i]);//all open braces get pushed onto the stack
				}else if(c[i]=='{') {
					pushCounter++;
					stack.push(c[i]);
				}else if(c[i]=='[') {
					pushCounter++;
					stack.push(c[i]);
				}else if(c[i]=='<') {
					pushCounter++;
					stack.push(c[i]);
				}else if(c[i]==')') {//checks to see if we can pop off the open brace if there is one
					if(stack.isEmpty()) {//if the stack is empty there is no open brace
						isEven=false;//input can not be 'Y'
                        i=c.length;//
					}else if(stack.peek().getChar() != '(') {//if the char on the stack is not the same open brace as the one passed in
						isEven=false;//the braces aren't even so is even is false
						i=c.length;//exit this input loop go to next input line
					}else {
						popCounter++;//if the stack is not empty and there is not an open brace on the top of the stack
                        stack.pop();// pop the stack and 1 to the pop counter
					}
				}else if(c[i]=='}') {
					if(stack.isEmpty()) {
						isEven=false;
					}else if(stack.peek().getChar() != '{') {
						isEven=false;
						i=c.length;
					}else {
						popCounter++;
						stack.pop();	
					}
				}else if(c[i]==']') {
					if(stack.isEmpty()) {
						isEven=false;
					}else if(stack.peek().getChar() != '[') {
						isEven=false;
						i=c.length;
					}else {
						popCounter++;
						stack.pop();	
					}
				}else if(c[i]=='>') {
					if(stack.isEmpty()) {
						isEven=false;
					}else if(stack.peek().getChar() != '<') {
						isEven=false;
						i=c.length;
					}else {
						popCounter++;
						stack.pop();	
					}
                }
			}
			if(isEven==true && stack.isEmpty() && pushCounter==popCounter) {//if isEven never got changed to false and the stack is Empty, and push and pop happen the same amount of times
				out.println("Y");//then print out Y
			}else {
				out.println("N");//if isEven is false or the stack is not Empty, or push and pop did not happen the same amount of times, print out N
			}
		}
		in.close();
		out.close();
	}
}

