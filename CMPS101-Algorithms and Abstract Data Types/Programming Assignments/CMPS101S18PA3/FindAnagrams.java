/*
 CREATED: Derrick DeBose May 14, 2018
 CHANGED: May 16, 2018
 
 FindAnagrams.java is the main codes that tests the Anagram ADT.
 The program reads in an input textfile that has the words of the dictionary in it.
 Each of those strings is converted into an anagram and added to an arraylist.
 After user input happens then the string is converted into an anagram.
 The user input anagram is compared with a key with each anagram in the arraylist.

*/
import java.util.*;
import java.io.*;

class FindAnagrams{
    public static void main(String[] args){
        
        if(args.length != 1) {//for correct amount of files read in
            System.out.println("Usage: java -jar PA3.jar <input text file>");
            System.exit(1);
        }
        try{//try block to be able to catch a file not found exception
            File inText = new File(args[0]);//file for input text file
            Scanner textFile = new Scanner(inText);//reads in text file
            Scanner in = new Scanner(System.in);//used to read in user input
            ArrayList<Anagram> list = new ArrayList<Anagram>();//an arraylist to hold my anagrams
            while (textFile.hasNextLine()) {//reads the text file in one line at a time
                String line = textFile.nextLine();//Input in string
                line = line.toLowerCase();
                Anagram a= new Anagram(line);//creates a new anagram from a string parameter
                list.add(a);//add current word in text file to the arraylist
            }
            System.out.println("type a string of letters");//intialize user input
            while (in.hasNextLine()){//reads in the scanner one line at a time
                
                String str = in.nextLine();//String generated from user input
                str = str.toLowerCase();//makes all the letters lower case
                if(str.equals("N")||str.equals("n")){//used to exit code
                    return;
                }else if(str.equals("Y")||str.equals("y")){//if you want to scan another anagram
                    System.out.println("type a string of letters");
                    in = in.reset();//resets scanner
                }else{
                    Anagram a = new Anagram(str);//makes an anagram from a string
                
                    for(int i=0; i<list.size();i++){//iterate through arraylist of anagrams
                        Anagram b = list.get(i);//get at the anagram at the current place in the loop
                        if(a.compare(a,b)){//compares the keys of anagrams
                            System.out.println(b.print(b));//print out the anagram in the list
                        }
                    }
                    System.out.println("Do another (y/n)?");
                }
            }
        }
        catch(FileNotFoundException e){//used to catch a file not found exception
            System.out.println("FileNotFoundException");
        }
    }
}
