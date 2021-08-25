
public class ChessPiece{
	int column;//variables used in the sub classes needs to be defined in super class and cant be redefined in the sub classes
	int row;
	int color;		
	ChessPiece(int col, int row, int color){
		column=col;
		this.row=row;
		this.color = color;
	}
		
	public boolean isAttacking(Object ChessPiece) {//wont ever run but needs in program because methods are found in the sub classes and those are the one we will be running in this program
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
		return "ChessPiece: "+ Integer.toString(column) + ' ' + Integer.toString(row) + ' '+ Integer.toString(color);
	}
}
