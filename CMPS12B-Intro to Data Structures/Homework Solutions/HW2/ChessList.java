
public class ChessList {
	public Node head;//start of list
	public int size;//size of how many objects were added
    public int kingCount = 0;//intialize kingCount to 0
	ChessList(){
		head = null;
		size=0;
	}
	public void add(Object ChessPiece) {//adds pieces into the linked list
		size++;
        if(ChessPiece instanceof King){//checks to see if the piece we adding to the list is a king
            kingCount++;//king counter
        }
		Node tempCP = new Node(ChessPiece);
		tempCP.next = head;
		head = tempCP;
	}
	public Node find (int x, int y) {//finds the node we checking to see if it is attacking
		for(Node tempCP=head; tempCP!=null; tempCP=tempCP.next) {//given to me in MSI, scans through full list
			ChessPiece chessP1 = (ChessPiece) tempCP.getObject();//created chess pieces in order to make it easier to call methods to the pieces.
			if(chessP1.getColumn() == x && chessP1.getRow() == y) {//if the piece we are on have the same x and y coordinates then as the the parameters passed in then return that node will be used in isAttack method in ChessList
				return tempCP;
			}
		}
		return null;
	}
	public boolean isValidList() {//checks if 2 pieces are on the same square and if there isn't more than one King with the same color
        if(kingCount < 2){//if there are 0 or 1 kings return false
            return false;
        }
		for(Node tempCP=head; tempCP!=null; tempCP=tempCP.next) {//given to me in MSI, scans through full list
			for(Node curr= tempCP.next; curr!=null; curr=curr.next) {//scans the list to compare 1,2 then 1,3 then move along the 2,3 to get every combination of 2 pieces
				ChessPiece chessP1 = (ChessPiece) tempCP.getObject();//created chess pieces in order to make it easier to call methods to the pieces.
				ChessPiece chessP2 = (ChessPiece) curr.getObject();
				if(chessP1.getColumn() == chessP2.getColumn() && chessP1.getRow() == chessP2.getRow()) {//if piece have same row and column return false
					return false;
				}
				if(chessP1 instanceof King && chessP2 instanceof King) {//https://www.javatpoint.com/downcasting-with-instanceof-operator where I learned how to use instanceof in order to check to see if pieces are of type King. This if statement is used to check to see if there are more than 2  kings
					if(chessP1.getColor() == chessP2.getColor()) {//If 2 kings have the same color return false
						return false;
					}
				}
			}
		}

		return true;
	}
	public boolean isAttack(Node Chess) {
		
		for(Node tempCP=head; tempCP!=null; tempCP=tempCP.next) {//given to me in MSI, scans through full list
			ChessPiece chessPiece = (ChessPiece)Chess.getObject();//creates a chess piece object of the piece we found
			if(chessPiece.isAttacking((ChessPiece)tempCP.getObject())) {//checks to see the piece we have is attacking the piece we are at in the list
				return true;
			}
		}
		return false;
	}
	public void printList() {//used for checking to see if I was creating actual chess piece objects
		for(Node curr=head;curr!=null;curr=curr.next) {
			System.out.println(curr.getObject().toString());
		}
	}
	public int getSize() {//used for checking to see if I added all the pieces into the array
		return size;
	}
}

