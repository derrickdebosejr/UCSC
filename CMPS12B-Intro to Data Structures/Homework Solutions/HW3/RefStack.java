
public class RefStack {
	Node top;
	RefStack(){//intializes the top of the nul to be null until things are put in
		top=null;
	}
	public boolean isEmpty() {//returns true if top is null
		return top == null;
	}
	public void push(char c) {//Make a new node that has a char and a reference to the previous top
		top = new Node(c, top);
	}
	public Node pop() {//removes the top node off the stack
		if(!isEmpty()) {//if the list is not empty
			Node temp = top;//creates a new node that has the same value as top
			top= top.next;//have top reference the whats next in the stack
			return temp;//return the node we just popped off
		}
		return top;//if empty there will be a null pointer exception
	}
	public Node peek() {
		if(!isEmpty()) {
			return top;//returns the top of the stack
		}
		return null;//if empty there will be a null pointer exception
	}
}

