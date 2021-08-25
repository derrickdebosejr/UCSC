public class Node {
	Object ChessPiece;
	Node next;
	
	Node(Object newChessPiece){
		ChessPiece= newChessPiece;
		next = null;
	}
	Node(Object newChessPiece, Node nextNode){//Node constructor to have a chess piece object and a reference to the next node
		ChessPiece = newChessPiece;
		next = nextNode;
	}
	public Object getObject() {//returns the chess piece object in the node
		return ChessPiece;
	}
}
