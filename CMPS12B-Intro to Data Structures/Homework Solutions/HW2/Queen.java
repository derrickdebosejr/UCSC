
public class Queen extends ChessPiece {
	
	Queen(int column, int row, int color){
		super(column,row,color);
	}
	
	public boolean isAttacking(Object ChessPiece) {//passes in the chess piece that was found using the find method
		int row2 = ((ChessPiece) ChessPiece).getRow();// used to differentiate between queen class row and the chess piece passed in row
		int column2 = ((ChessPiece) ChessPiece).getColumn();
		int color2 = ((ChessPiece) ChessPiece).getColor();
		int diagCheck= column2+row2;
		int diagCheck2=column2-row2;
		//Checks if queen is in same color as the chess piece
		if (color == color2) {//already checked for a valid board so if they the same color it doesn't matter return false
			return false;
		}
		else {
			//Checks if pieces are in the same column
			if(column==column2) {
				return true;
			}
			//Checks if queen is in the same row
			if(row==row2) {
				return true;
			}
			//checks to see if a queen is attacking from bottom left to top right diagonal
			if(row+column== diagCheck) {
				return true;
			}
			//checks to see if queen is attacking from top left to bottom right diagonal
			if(column-row==diagCheck2) {
				return true;
			}
		}
		return false;
	}
	public int getColumn() {
		return column;
	}
	public int getRow() {
		return row;
	}
	public int getColor() {
		return color;
	}
	public String toString() {
		if (color ==0) {//lower case if was color == 0(white)
			return "q";
		}else {
			return "Q";
		}
	}
}

