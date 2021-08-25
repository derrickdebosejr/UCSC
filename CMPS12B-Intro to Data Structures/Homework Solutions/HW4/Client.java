public class Client{
    String name;
    int arrival;
    int departure;
    int transaction;
    int start;
    int wait;
    int teller;
    boolean checker = true;// intialize checker to being true
    public Client(String name, int arrival, int transaction,int teller){//constructor to make client objects
        this.name = name;
        this.arrival=arrival;
        this.transaction=transaction;
        this.teller = teller;
    }
    String getName(){//returns the name of the client
        return name;
    }
    int getStart(){//returns the start time of client
        return start;
    }
    int getDeparture(){//returns the departure time of client
        return departure;
    }
    boolean getChecker(){//returns the checker of client
        return checker;
    }
    int getArrival(){//returns the arrival time of client
        return arrival;
    }
    int getTransaction(){//returns the transaction time of client
        return transaction;
    }
    int getWait(){//returns the wait time of client
        return wait;
    }
    
}
