import java.util.*;
import java.io.*;

public class NQueens {
	int chessBoard[][];
	static int queensCounter = 0;
	static int column;
	static int BoardSize;
	static int firstCol;
	static int firstRow;
	static BufferedReader fileInput;
	static String line;
	
	public static void main(String[] args) throws IOException {
		fileInput = new BufferedReader(new FileReader(args[0]));
		BufferedWriter out = new BufferedWriter(new FileWriter(args[1]));		
		while ((line= fileInput.readLine()) !=null) {
			char[] c = line.toCharArray();
			BoardSize = Character.getNumericValue(c[0]);
			System.out.println("BoardSize " + BoardSize);
			firstCol = Character.getNumericValue(c[2]);
			System.out.println("firstCol " + firstCol);
			firstRow = Character.getNumericValue(c[4]);
			System.out.println("firstRow " + firstRow);
			out.write("hello");
		}
		NQueens queen = new NQueens();
		queen.clearBoard();
		queen.displayBoard();
		queen.setQueen(firstCol, firstRow);
		queen.placeQueens(0);
		if(!queen.placeQueens(0)) {
			queen.printQueens(out);
		}
		else {
			out.write("no solution");
		}
		fileInput.close();
		out.close();
		
	}
	public NQueens() {
		chessBoard = new int[BoardSize][BoardSize];
	}
	public void clearBoard() {
		for (int i=0;i <  BoardSize;i++) {
			for(int j=0;j < BoardSize;j++) {
				chessBoard[j][i]= 0;
			}
		}
	}
	public void displayBoard() {
		for (int i=0;i <  BoardSize;i++) {
			for(int j=0;j < BoardSize;j++) {
				System.out.print(chessBoard[i][j]);//goes through array and prints each int in 2D array
			}
			System.out.println();
		}
		System.out.println();
	}
	public boolean isUnderAttack(int column, int row) {//pass in x,y coordinates
		//Checks if queen is in same column
		for( int i= 0; i<BoardSize; i++) {
			System.out.println("column is" + column);
			System.out.println("row is" + row);
			if(chessBoard[column][i] == 1) {
				return true;
			}
		}
		//Checks if queen is in the same row
		for( int i= 0; i< BoardSize; i++) {
			System.out.println("column is" + column);
			System.out.println("row is " + row);
			if(chessBoard[i][row] == 1) {
				return true;
			}
		}
		//checks to see if a queen is attacking from bottom left to top right diagonal
		int check = row+column;
		for( int i= 0; i< BoardSize; i++){
			for(int j = 0; j< BoardSize; j++) {
				System.out.println("i+j is "+ i+j + " and check is " + check);
				if(i+j == check) {
					if(chessBoard[i][j] == 1) {
						return true;
					}
				}
			}
		}
		//checks to see if queen is attacking from top left to bottom right diagonal
		int check2=column-row;
		for( int i= row; i< BoardSize; i++){
			for(int j = column; j< BoardSize; j++) {
				if(j-i == check2) {
					if(chessBoard[i][j] == 1) {
						return true;
					}
				}
			}
		}
		return false;
	}
	public boolean placeQueens(int column) {
		//base case
		if (queensCounter == BoardSize) {
			return true;
		}
		else {
			int row = 0;//0 is the array index
			boolean queenPlaced = false;// queenPlaced is the check to see if we have placed all the queens
			while(!queenPlaced && row < BoardSize) {
				if(isUnderAttack(column,row)) {
					row++;
				}
				else {
					setQueen(column,row);
					row=0;
					placeQueens(column+1);
					System.out.println("column is " + column);
				}
				if(!queenPlaced) {
					removeQueen(column,row);
					row=0;
					placeQueens(column-1);
				}
				return queenPlaced;
			}
		}
		return false;
	}
	private void setQueen(int column, int row) {
		chessBoard[column][row] = 1;
		queensCounter++;
		displayBoard();
		
	}
	private void removeQueen(int column, int row) {
		chessBoard[column][row] = 0;
		queensCounter--;
		displayBoard();
	}
	public void printQueens(BufferedWriter out) throws IOException {
		for( int i= 0; i< BoardSize; i++){
			for(int j = 0; j< BoardSize; j++) {
				if(chessBoard[j][i] == 1) {
					out.write(i+1 + ' ' + j+1 + ' ');
				}
			}
		}
	}
}
