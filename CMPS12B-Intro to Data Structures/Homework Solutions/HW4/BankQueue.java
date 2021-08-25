public class BankQueue{
    Node lastNode;
    
    public BankQueue(){//queue constructor
        lastNode = null;
    }
    public boolean isEmpty(){
        return lastNode==null;//if the lastNode is null return true
    }
    public void dequeueAll(){//dequeues the entire queue
        lastNode=null;
    }
    public void enqueue(Client item){
        Node newNode = new Node(item);//node to add to queue
        
        if(isEmpty()){//if the queue is empty
            newNode.next = newNode;//the only in the queue references itself
        }
        else{
            newNode.next= lastNode.next;//the new node points what the last node points to
            lastNode.next = newNode;// the last node now points to the new node added
        }
        lastNode=newNode;//the last node is now the new node passed in
    }
    public Client dequeue(){//gets rid of the front queue
        if(isEmpty()){//if the list is empty
            return null;//return null
        }else{
            Node firstNode=lastNode.next;//used a temporary node
            if(firstNode == lastNode){//special case if there is only one node in the queue
                lastNode=null;//lastNode is now null
                return firstNode.getObject();//return the node dequeued
            }else{
                lastNode.next = firstNode.next;//change the reference of the last node
                return firstNode.getObject();//return the nide dequeued
            }
        }
        
    }
    public Node peek(){//returns the front of the node
        if(isEmpty()){//if the queue is empty
            return null;//the front is null
        }else{
            return lastNode.next;//the front is lastNode.next
        }
    }
    public void waitCounter(int time){//method used to check if the people remaining in the queue have already arrived and increments wait by one to each client that their arrival time is<= time
        if(!isEmpty()){//if the list is not empty
            Node curr = lastNode.next;
            if(curr == lastNode){
                return;
            }else{
                for(curr = lastNode.next; curr!=lastNode;curr=curr.next){//scan through entire list
                    Client client= curr.getObject();//create a client for each node
                    if(time>=client.getArrival()){//if the time is >= arrival time
                        client.wait++;//that client has to wait at the time passed in so imcrement wait by 1
                    }
                }
                curr = lastNode;//for loop never evaluates the last node in the queue
                Client client= curr.getObject();//creates a client for the last node
                if(time>=client.getArrival()){//if the time is >= arrival time
                    client.wait++;//that client has to wait at the time passed in so imcrement wait by 1
                }
            }
            
        }
        
    }
}
