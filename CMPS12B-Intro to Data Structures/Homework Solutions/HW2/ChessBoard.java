import java.util.*;
import java.io.*;


public class ChessBoard {
	public static void main (String[] args) throws IOException{
		if(args.length< 2) {
			System.out.println("Usage: java -jar ChessBoard.jar <input file> <output file>");
			System.exit(1);
		}		
		File inFile = new File(args[0]);
        File outFile = new File(args[1]);
		Scanner in = new Scanner(inFile);//reads in arguments
		PrintWriter out = new PrintWriter(outFile);//prints into the out.txt file
		
		while(in.hasNextLine()) {//reads in input one line at a time
			ChessList list = new ChessList();//creates a new list each time a new line is read in
			int findCol=0;//variables need to be intialized each time we read in a line of input
			int findRow=0;
			String line = in.nextLine();
			String [] token = line.split(":");//token is now 2 arrays 1st array is the (x,y) coordinate and the 2nd array is the chess pieces that need to be added in
			int totalString = token.length;//totalString will always be 2
			for(int i=0; i< totalString; i++) {
				if(i%2 ==0) {//If token[0] then save the input
					// store column and row this is the piece we need to find
					char[] c= token[i].toCharArray();//converts string to an array of char
					findCol =Character.getNumericValue(c[0]);//converts char to int
					findRow =Character.getNumericValue(c[2]);
				}
				else if(i%2==1) {//if token[1] create chess pieces
					
					char[] c= token[i].toCharArray();//converts string to an array of char
					int a=0;//counter to see if I made it to the end out the list 
					while( a<c.length) {// while we are still in the range of the char array
						if(c[a]=='K') {//black king
							int x= Character.getNumericValue(c[a+2]);//weird indexes because I had to account for white space
							int y= Character.getNumericValue(c[a+4]);//x,y coordinates to put into the king object
							ChessPiece king = new King(x,y,1);//creates a chess piece of type king
							list.add(king);//adds the king to the list
							a=a+4;//increment to the y coordinate because if there is no space at the end the word and can check to see if we are at the end of the line
						} else if(c[a]=='k') {//creates white king and adds the piece into the list
							int x= Character.getNumericValue(c[a+2]);
							int y= Character.getNumericValue(c[a+4]);
							ChessPiece king = new King(x,y,0);
							list.add(king);
							a=a+4;
						} else if(c[a]=='Q') {//creates black queen and adds the piece into the list
							int x= Character.getNumericValue(c[a+2]);
							int y= Character.getNumericValue(c[a+4]);
							Queen queen = new Queen(x,y,1);
							list.add(queen);
							a=a+4;
						} else if(c[a]=='q') {//creates white queen and adds the piece into the list
							int x= Character.getNumericValue(c[a+2]);
							int y= Character.getNumericValue(c[a+4]);
							ChessPiece queen = new Queen(x,y,0);
							list.add(queen);
							a=a+4;
						}else if(c[a]=='R') {//creates black rook and adds the piece into the list
							int x= Character.getNumericValue(c[a+2]);
							int y= Character.getNumericValue(c[a+4]);
							ChessPiece rook = new Rook(x,y,1);
							list.add(rook);
							a=a+4;
						}else if(c[a]=='r') {//creates white rook and adds the piece into the list
							int x= Character.getNumericValue(c[a+2]);
							int y= Character.getNumericValue(c[a+4]);
							ChessPiece rook = new Rook(x,y,0);
							list.add(rook);
							a=a+4;
						}else if(c[a]=='B') {//creates black bishop and adds the piece into the list
							int x= Character.getNumericValue(c[a+2]);
							int y= Character.getNumericValue(c[a+4]);
							ChessPiece bishop = new Bishop(x,y,1);
							list.add(bishop);
							a=a+4;
						}else if(c[a]=='b') {//creates white bishop and adds the piece into the list
							int x= Character.getNumericValue(c[a+2]);//plus 2 because I know there will be a space after the letter
							int y= Character.getNumericValue(c[a+4]);
							ChessPiece bishop = new Bishop(x,y,0);
							list.add(bishop);
							a=a+4;
						}//end else if
						a++;//if we are not at a letter increment a
					}//end while
					
				}//end if/else

			}//end for
			if(!list.isValidList()) {//checks for a valid list
				out.println("Invalid");
				
			} else if(list.find(findCol, findRow)==null) {//if the list is valid then try to find the piece from user input
				out.println("-");
			}else {
				out.print(list.find(findCol, findRow).getObject().toString());//if we found piece print out which letter/piece it is
				if(list.isAttack(list.find(findCol, findRow))) {//tells if the piece we found is attacking anther piece
					out.println(" y");
				}else {
					out.println(" n");
				}
			//needs be in a big if else statement in order to move to next line if board is invalid and or cant find the piece
			}//end if
		}//end while loop
			
		
		in.close();
		out.close();		
	}//end main
}//end class

