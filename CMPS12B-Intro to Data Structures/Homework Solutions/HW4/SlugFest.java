import java.io.*;
import java.util.*;

class SlugFest{
    public static void main(String args[]) throws IOException {
        if(args.length< 2) {
            System.out.println("Usage: java -jar ChessBoard.jar <input file> <output file>");
            System.exit(1);
        }
        File inFile = new File(args[0]);
        File outFile = new File(args[1]);
        Scanner in = new Scanner(inFile);//reads in arguments
        PrintWriter out = new PrintWriter(outFile);//prints into the out.txt file
        
        BankQueue teller1 = new BankQueue();//make 5 queues for the 5 tellers that we have to keep track of
        BankQueue teller2 = new BankQueue();
        BankQueue teller3 = new BankQueue();
        BankQueue teller4 = new BankQueue();
        BankQueue teller5 = new BankQueue();
        
        while (in.hasNextLine()) {//reads input in one line at a time
            String line = in.nextLine();
            String [] token = line.split("\\s+");//Split the string at all white spaces
            int totalString = token.length;
            int arrival=0;//intialize each customers variables to 0 and null
            int teller=0;
            int transactiontime=0;
            String client=null;
            char[] c = token[0].toCharArray();//used to get teller number
            teller =  Character.getNumericValue(c[0]);// used for the switch case to put each client in the right line
            char[] d = token[1].toCharArray();//used to get name of client
            char[] name = new char[d.length];
            for(int j= 0; j< token[1].length(); j++){
                name[j]= d[j];//saves the name in a char array
            }
            client = String.valueOf(name);//converts char array to string
            arrival = Integer.parseInt(token[2]);//converts char to int
            transactiontime= Integer.parseInt(token[3]);//converts char to int
            Client customer = new Client(client,arrival,transactiontime,teller);//creates a client object to put in the queue
            switch(teller){//enqueue entire input before trying to compute anything
                case 1:
                    teller1.enqueue(customer);//enqueues object client to queue
                    break;
                case 2:
                    teller2.enqueue(customer);
                    break;
                case 3:
                    teller3.enqueue(customer);
                    break;
                case 4:
                    teller4.enqueue(customer);
                    break;
                case 5:
                    teller5.enqueue(customer);
                    break;

            }
            
        }//end while
        int time = 0 ;//intialize time to 0
        while(!teller1.isEmpty() || !teller2.isEmpty() || !teller3.isEmpty() || !teller4.isEmpty() || !teller5.isEmpty()){//loop until every queue is empty
            if(!teller1.isEmpty()){//if the list in not empty
                Client client1 = teller1.peek().getObject();//creates a client that points to the front of the queue
                if(client1.getArrival()==time||client1.getArrival()+client1.getWait()==time){//if the person at the front of the line arrives at the current time or arrival time plus their wait time is equal to current time
                    if(client1.getChecker()){//the checker is set to true and changed to false when start and departure are set
                        client1.start=time;//set start time of front client
                        client1.departure= client1.start + client1.transaction;//set departure time for from of the queue
                        client1.checker=false;//sets checker to false to make sure departure never gets changed again
                        out.println("1 "+ client1.getName() + " begins " + client1.getStart());//prints statement to the out file
                    }
                }
                if(client1.getDeparture()==time&&client1.getDeparture()!=0){//if time is equal to the departure and you cannot depart at time 0
                    out.println("1 " + client1.getName() + " ends " + time);//print out the statement for when the person ends
                    teller1.dequeue();//dequeue the from of the list
                    if(!teller1.isEmpty()){//if the list is not empty(if statement is used to check if the next person in the queue has been waiting because has to be evauated at the same time)
                        client1 = teller1.peek().getObject();//creates a client that points to the front of the queue
                        if(client1.getArrival()+client1.getWait()==time){//arrival time plus their wait time is equal to current time
                            client1.start=time;//set start time of front client
                            client1.departure= client1.start + client1.transaction;//set departure time for from of the queue
                            client1.checker=false;//sets checker to false to make sure departure never gets changed again
                            out.println("1 "+ client1.getName() + " begins " + client1.getStart());//prints out the time they start
                        }
                    }
                }
                teller1.waitCounter(time);//method in my queue class to check if the people remaining in the queue have already arrived and increments wait by one to each client that their arrival time is<= time
            }
            if(!teller2.isEmpty()){//same logic used from the teller1 queue
                Client client2 = teller2.peek().getObject();
                if(client2.getArrival()==time||client2.getArrival()+client2.getWait()==time){
                    if(client2.getChecker()){
                        client2.start=time;
                        client2.departure= client2.start + client2.transaction;
                        client2.checker=false;
                        out.println("2 "+ client2.getName() + " begins " + client2.getStart());
                    }
                }
                if(client2.getDeparture()==time&&client2.getDeparture()!=0){
                    out.println("2 " + client2.getName() + " ends " + time);
                    teller2.dequeue();
                    if(!teller2.isEmpty()){
                        client2 = teller2.peek().getObject();
                        if(client2.getArrival()+client2.getWait()==time){
                            client2.start=time;
                            client2.departure= client2.start + client2.transaction;
                            client2.checker=false;
                            out.println("2 "+ client2.getName() + " begins " + client2.getStart());
                        }
                    }
                }
                teller2.waitCounter(time);
            }
            if(!teller3.isEmpty()){//same logic used from the teller1 queue
                Client client3 = teller3.peek().getObject();
                if(client3.getArrival()==time||client3.getArrival()+client3.getWait()==time){
                    if(client3.getChecker()){
                        client3.start=time;
                        client3.departure= client3.start + client3.transaction;
                        client3.checker=false;
                        out.println("3 "+ client3.getName() + " begins " + client3.getStart());
                    }
                }
                if(client3.getDeparture()==time&&client3.getDeparture()!=0){
                    out.println("3 " + client3.getName() + " ends " + time);
                    teller3.dequeue();
                    if(!teller3.isEmpty()){
                        client3 = teller3.peek().getObject();
                        if(client3.getArrival()+client3.getWait()==time){
                            client3.start=time;
                            client3.departure= client3.start + client3.transaction;
                            client3.checker=false;
                            out.println("3 "+ client3.getName() + " begins " + client3.getStart());
                        }
                    }
                }
                teller3.waitCounter(time);
            }
            if(!teller4.isEmpty()){//same logic used from the teller1 queue
                Client client4 = teller4.peek().getObject();
                if(client4.getArrival()==time||client4.getArrival()+client4.getWait()==time){
                    if(client4.getChecker()){
                        client4.start=time;
                        client4.departure= client4.start + client4.transaction;
                        client4.checker=false;
                        out.println("4 "+ client4.getName() + " begins " + client4.getStart());
                    }
                }
                if(client4.getDeparture()==time&&client4.getDeparture()!=0){
                    out.println("4 " + client4.getName() + " ends " + time);
                    teller4.dequeue();
                    if(!teller4.isEmpty()){
                        client4 = teller4.peek().getObject();
                        if(client4.getArrival()+client4.getWait()==time){
                            client4.start=time;
                            client4.departure= client4.start + client4.transaction;
                            client4.checker=false;
                            out.println("4 "+ client4.getName() + " begins " + client4.getStart());
                        }
                    }
                    
                }
                teller4.waitCounter(time);
            }
            if(!teller5.isEmpty()){//same logic used from the teller1 queue
                Client client5 = teller5.peek().getObject();
                if(client5.getArrival()==time||client5.getArrival()+client5.getWait()==time){
                    if(client5.getChecker()){
                        client5.start=time;
                        client5.departure= client5.start + client5.transaction;
                        client5.checker=false;
                        out.println("5 "+ client5.getName() + " begins " + client5.getStart());
                    }
                }
                if(client5.getDeparture()==time&&client5.getDeparture()!=0){
                    out.println("5 " + client5.getName() + " ends " + time);
                    teller5.dequeue();
                    if(!teller5.isEmpty()){
                        client5 = teller5.peek().getObject();
                        if(client5.getArrival()+client5.getWait()==time){
                            client5.start=time;
                            client5.departure= client5.start + client5.transaction;
                            client5.checker=false;
                            out.println("5 "+ client5.getName() + " begins " + client5.getStart());
                        }
                    }
                    
                }
                teller5.waitCounter(time);
            }
            time++;//increment time after checking each queue has be evaluated at current time
        }//end while
        in.close();
        out.close();
    }//end main
}//end class
