import java.io.*;
import java.util.*;
import java.util.HashMap;

class Bard{
    public static void main(String[] args){
        if(args.length != 3) {//for correct amount of files read in
            System.out.println("Usage: java -jar Bard.jar <input text file> <input file> <output file>");
            System.exit(1);
        }
        try{//try block to be able to catch a file not found exception
            File inText = new File(args[0]);//file for input text file
            File inFile = new File(args[1]);//file for input file
            File outFile = new File(args[2]);//file for output fiel
            Scanner in = new Scanner(inFile);//reads in arguments
            Scanner textFile = new Scanner(inText);//reads in text file
            PrintWriter out = new PrintWriter(outFile);//prints into the out.txt file
            HashMap<String, Integer> hm = new HashMap<String, Integer>();
            while (textFile.hasNextLine()) {//reads the text file in one line at a time
                String line = textFile.nextLine();//Input in string
                String [] token = line.split("[^a-zA-Z]");//Split the string at all white spaces and punctuation
                int totalString = token.length;//used to know how many words are in each line
                for(int i=0;i<totalString; i++) {//go through full line of input array
                    String key = token[i];//key for hashmap
                    if(hm.containsKey(key)){//if the hashmap has this key
                        int keyValue = hm.get(key);//get the value of key
                        hm.remove(key);//remove the key
                        keyValue++;//increment value
                        hm.put(key,keyValue);//put key back into hashmap
                    }else{
                        hm.put(token[i], 1);//if the key is not found there is the only one of that key
                    }
                }
            }
            Word[] word = new Word[hm.size()];//create an array of word objects
            word = bubbleSort(hm);//bubbleSort takes in the hashmap and return an array of word objects
            /* used for testing
             for(int i=0; i<word.length;i++){
                out.println(word[i].toStrin());
            }*/
            while(in.hasNextLine()){//reads in the input one line at time now that we have sorted data and our hashmap
                String line = in.nextLine();//Input in string
                String [] token = line.split("\\s+");//Split the string at all white spaces
                int totalString = token.length;//totalStrong is used to determine if input is 1 word or 2 numbers
                if(totalString==1){//if a word input
                    String input = token[0];//our key input
                    if(hm.containsKey(input)){//if hashmap contains this key
                        int value = hm.get(input);//get the value
                        out.println(input +' '+ value);//print out the name with the number of occurences
                    }else
                        out.println(input + " 0");//if there is nothing to find in hashmap then print out "name 0" 0 being occurences
                }
                if(totalString ==2){//if 2 number inputs
                    int charLength = Integer.parseInt(token[0]);//length of the word we are looking for
                    int rate = Integer.parseInt(token[1]);//how many words we need to print out
                    for(int i=0; i<word.length && rate!=0; i++){//sorted by highest frequency so
                        if(word[i].getLength()==charLength){//if the word we are has the same charlength then its the most frequent
                            out.print(word[i].getName()+ " ");//print out name with a space
                            rate--;//decrement rate
                        }
                    }
                    while(rate != 0){//used for if there are not enough words of a certain character length
                        out.println("- ");//print out a - for every word not found of that length
                        rate--;//decrement rate
                    }
                    if (rate == 0){//if rate is now 0
                        out.println();//new line output is over
                    }
                    
                }
            }
            in.close();//close files used
            textFile.close();
            out.close();
        }
        catch(FileNotFoundException e){//used to catch a file not found exception
            System.out.println("FileNotFoundException");
        }
        
    }
    public static Word[] bubbleSort(HashMap<String,Integer> map){//used a bubble sort our map and return a sorted array of words
        ArrayList<Word> array = new ArrayList<Word>(map.size());//creates an arraylist of the size of our hashmap
        for(String key : map.keySet()){//traverse through the map
            Word word = new Word(key,map.get(key),key.length());//create a word object of the current place in map
            array.add(word);//add word to arraylist
        }
        Word[] word = new Word[array.size()];//create an array of words of size of arraylist
        for(int i=0; i<array.size();i++){//for loop to go the array list
            word[i] = array.get(i);//convert arraylist to word array
        }
        boolean sorted=false;//false when swap occurs
        for(int i=1 ;i<word.length && !sorted; ++i){
            sorted = true;//assume sorted
            for(int index =0; index<map.size()-i;index++){
                int nextIndex = index+1;
                if(nextIndex==map.size()){//we are done sorting
                    sorted=true;
                }else{
                    if(word[index].value < word[nextIndex].value){//sort by high occurence being at the front of the list
                        Word temp = word[index];//exchanges the 2 indexes
                        word[index] = word[nextIndex];
                        word[nextIndex]= temp;
                        sorted = false;//not sorted list if just exchanged
                    }
                }
            }
        }
        return word;//return our array of words sorted by highest occurence
    }
}

