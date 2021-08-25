
public class Node {
	Client client;
	Node next;
	
	Node(Client client){
		this.client=client;
		next = null;
	}
	Node(Client client, Node nextNode){//Node constructor to have a client and a reference to the next node in the Queue
		this.client = client;
		next = nextNode;
	}
	public Client getObject() {//returns the client in the node
		return client;
	}
}
