//Creates word objects to store the data of the hashmap
class Word{
    String name;//name or key of hashmap
    int value;//value of hashmap
    int length;//length of the name
    Word(String name,int value,int length){//word constructor
        this.name = name;
        this.value = value;
        this.length = length;
    }
    String getName(){//method to get name of object word
        return name;
    }
    int getValue(){//method to get value of object word
        return value;
    }
    int getLength(){//method to get length of object word
        return length;
    }
    String toStrin(){//my toString method used for testing
        return name+ " "+value+ " "+length;
    }
}
