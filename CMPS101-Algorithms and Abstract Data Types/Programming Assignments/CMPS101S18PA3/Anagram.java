/*
 CREATED: Derrick DeBose May 14, 2018
 CHANGED: May 16, 2018
 
 Anagram.java is the ADT that creates anagrams. A new anagram can be made with a string or a char array.
 A key is made for the anagram based on a unique factorization for each anagram because each letter is
 assigned a unique prime number. Print returns the string in the anagram ADT and compare return true if
 the 2 anagrams passed in are anagrams of each other.

*/
class Anagram{
    int key = 1;//key needs to intialized to 1 because if it were 0 all of our keys would be 0
    String str;//the string of the anagram
    
    /*
     this constructor takes in a String and assigns a prime number to each letter and the product of the
     primes creates a unique factorization
     */
    Anagram(String str){
        char[] c = str.toCharArray();
        this.str=str;
        //assigns a prime number to each letter.A product of primes is a unique factoriztorization
        for(int i=0;i<c.length;i++){
            switch (c[i]){
                case 'A':
                case 'a': key = key * 2;//first prime number
                
                case 'B':
                case 'b': key = key * 3;//second prime number
                
                case 'C':
                case 'c': key = key * 5;
                
                case 'D':
                case 'd': key = key * 7;
                
                case 'E':
                case 'e': key = key * 11;
                
                case 'F':
                case 'f': key = key * 13;
                
                case 'G':
                case 'g': key = key * 17;
                
                case 'H':
                case 'h': key = key * 19;
                
                case 'I':
                case 'i': key = key * 23;
                
                case 'J':
                case 'j': key = key * 29;
                
                case 'K':
                case 'k': key = key * 31;
                
                case 'L':
                case 'l': key = key * 37;
                
                case 'M':
                case 'm': key = key * 41;
                
                case 'N':
                case 'n': key = key * 43;
                
                case 'O':
                case 'o': key = key * 47;
                
                case 'P':
                case 'p': key = key * 53;
                
                case 'Q':
                case 'q': key = key * 59;
                
                case 'R':
                case 'r': key = key * 61;
                
                case 'S':
                case 's': key = key * 67;
                
                case 'T':
                case 't': key = key * 71;
                
                case 'U':
                case 'u': key = key * 73;
                
                case 'V':
                case 'v': key = key * 79;
                
                case 'W':
                case 'w': key = key * 83;
                
                case 'X':
                case 'x': key = key * 89;
                
                case 'Y':
                case 'y': key = key * 97;
                
                case 'Z':
                case 'z': key = key * 101;
                
            }//end switch
        }//end for loop
    }//end constructor
    
    /*
    this constructor takes in an array of char and assigns a prime number to each letter and the product of the
    primes creates a unique factorization
    */
    Anagram(char[] c){
        str = new String(c);
        for(int i=0;i<c.length;i++){//got through the entire string
            //assigns a prime number to each letter. A product of primes is a unique factoriztorization
            switch (c[i]){
                case 'A':
                case 'a': key = key * 2;
                    
                case 'B':
                case 'b': key = key * 3;
                    
                case 'C':
                case 'c': key = key * 5;
                    
                case 'D':
                case 'd': key = key * 7;
                    
                case 'E':
                case 'e': key = key * 11;
                    
                case 'F':
                case 'f': key = key * 13;
                    
                case 'G':
                case 'g': key = key * 17;
                    
                case 'H':
                case 'h': key = key * 19;
                    
                case 'I':
                case 'i': key = key * 23;
                    
                case 'J':
                case 'j': key = key * 29;
                    
                case 'K':
                case 'k': key = key * 31;
                    
                case 'L':
                case 'l': key = key * 37;
                    
                case 'M':
                case 'm': key = key * 41;
                    
                case 'N':
                case 'n': key = key * 43;
                    
                case 'O':
                case 'o': key = key * 47;
                    
                case 'P':
                case 'p': key = key * 53;
                    
                case 'Q':
                case 'q': key = key * 59;
                    
                case 'R':
                case 'r': key = key * 61;
                    
                case 'S':
                case 's': key = key * 67;
                    
                case 'T':
                case 't': key = key * 71;
                    
                case 'U':
                case 'u': key = key * 73;
                    
                case 'V':
                case 'v': key = key * 79;
                    
                case 'W':
                case 'w': key = key * 83;
                    
                case 'X':
                case 'x': key = key * 89;
                    
                case 'Y':
                case 'y': key = key * 97;
                    
                case 'Z':
                case 'z': key = key * 101;
                    
            }//end switch
        }//end for loop
    }//end constructor
    
    /*
    The print method returns the string stored in the anagram
    */
    String print(Anagram a){
        
        return a.str;//return the string of the anagram
    }
    
    /*
    The compare method compares 2 anagrams passed in the parameters based on their keys and runs in O(1) time.
    */
    Boolean compare(Anagram a, Anagram b){
        if(a.key==b.key){// if the keys are the same
            if(a.str.compareTo(b.str)!=0){//if anagrams check to see if the strings aren't the same string
                return true;
            }
            return false;
        }
        else{
            return false;
        }
    }
    
}
