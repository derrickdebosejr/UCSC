import java.util.*;
import java.io.*;
public class PA1{
    public static void main(String[] args) throws IOException{
        if(args.length<2){
            System.out.println("Usage: java -jar PA1.jar <input file> <output file>");
            System.exit(1);
        }
        
        File inFile = new File(args[0]);
        Scanner in = new Scanner(inFile);
        PrintWriter out = new PrintWriter(args[1]);
        int c = -3234871;//can be used to make an apint
        String zero="0";
        while(in.hasNextLine()){
            String line = in.nextLine();
            int length = line.length();
            if(line.contains("+")){//if an add method/ or positive number
                String[] arr = line.split("\\+");//split at the +
                if(arr[0].isEmpty()){//check for just a positive number
                    apint foo = new apint(arr[1]);//one number to deal with
                    out.println(foo.print(foo));
                }else{
                    apint one= new apint(arr[0]);//make one apint
                    apint two= new apint(arr[1]);//make another apint
                    apint s= new apint();//somewhere to store the sum
                    s=s.addition(one,two);//add the numbers
                    out.println(s.print(s));//print the sum
                }
            }else if (line.contains(".")){//if an decimal number
                String[] arr = line.split("\\.");//split at the .
                if(arr[0]== zero||arr[0].isEmpty()){//check for just a 0 in front of decimal or decimal
                    apint one=new apint();//make one apint
                    out.println(one.print(one));//print
                }else {
                    apint one = new apint(arr[0]);//makes an apint with the front number
                    out.println(one.print(one));//print
                }
                
            }
            else if(line.contains("*")){//if a multiply method
                String[] arr = line.split("\\*");//split at the *
                apint one= new apint(arr[0]);
                apint two= new apint(arr[1]);
                apint s= new apint();//somewhere to store the product
                s=s.multiply(one,two);//multiply the numbers
                out.println(s.print(s));//print
            }else if(line.contains("/")){//if a divide method
                String[] arr = line.split("\\/");//split at the /
                apint one= new apint(arr[0]);
                apint two= new apint(arr[1]);
                apint s= new apint();//somewhere to store the quotient
                s=s.divide(one,two);//divide the numbers
                out.println(s.print(s));//print
            }else if(line.contains("-")){// if negative number or subtraction
                String[] arr = line.split("\\-");//split at the -
                int len = arr.length;
                if(arr[0].isEmpty()){//check for a negative number
                    apint foo = new apint(line);//make the number
                    out.println(foo.print(foo));//print
                }else{//need to subtract
                    apint one= new apint(arr[0]);
                    apint two= new apint(arr[1]);
                    apint s= new apint();//somewhere to store the difference
                    s=s.subtraction(one,two);//subtract the numbers
                    out.println(s.print(s));//print
                }
            }else if(line.contains("!")){//if a factorial function
                String[] arr = line.split("\\!");//split at the !
                apint fact= new apint(arr[0]);
                int factor = Integer.parseInt(arr[0]);// an int is passed to factorial
                fact=fact.factorial(factor);//do the factorial operation
                out.println(fact.print(fact));//print
            }
            else{//else just print out the number
                apint foo = new apint(line);
                out.println(foo.print(foo));
            }
        }
        in.close();
        out.close();
    }
}
