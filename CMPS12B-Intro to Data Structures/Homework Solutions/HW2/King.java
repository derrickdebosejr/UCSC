
public class King extends ChessPiece{

	King(int column, int row, int color){
		super(column,row,color);
	}
	
	public boolean isAttacking(Object ChessPiece) {//passes in the chess piece that was found using the find method
		int row2 = ((ChessPiece) ChessPiece).getRow();// used to differentiate between king class row and the chess piece passed in row
		int column2 = ((ChessPiece) ChessPiece).getColumn();
		int color2 = ((ChessPiece) ChessPiece).getColor();
		if(color2==color) {//already checked for a valid board so if they the same color it doesn't matter return false
			return false;
		}
		else if(column2-1==column && row2+1==row || column2==column && row2+1==row || column2+1==column && row2+1==row ||//row+1 and column -1 through +1
				column2-1==column && row2==row || column2+1==column && row2==row ||//checks row+0 check left and right column spaces
				column2-1==column && row2-1==row ||column2 == column && row2+1==row ||column2-1==column && row2+1==row ||column2+1==column && row2+1==row ) {//checks row-1 and column -1 through +1
			return true;//large if statement in order to check all 8 spaces around the king it can attack
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
			return "k";
		}else {
			return "K";
		}
	}
}

