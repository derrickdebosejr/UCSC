
public class Node {
	char c;
	Node next;
	
	Node(char c){
		this.c=c;;
		next = null;
	}
	Node(char c, Node nextNode){//Node constructor to have a char and a reference to the next node in the Stack
		this.c = c;
		next = nextNode;
	}
	public char getChar() {//returns the char in the node
		return c;
	}
}
