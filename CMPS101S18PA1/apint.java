
public class apint{
    static final int MAXARRAY = 3000;
    int[] number = new int[MAXARRAY];
    String num;
    int numberlen;
    boolean negative = false;
    apint(){//default constructor, allocates memory for apint
        int[] number= new int[MAXARRAY];
    }
    apint(String num){//converts a string of ints to an apint that has a flag to determine if number is negative or not
        this.num=num;//intialize the string of numbers
        char c[] = num.toCharArray();
        int str= c.length-1;
        int[] number= new int[MAXARRAY];
        if(c[0]== '-'){//checks if the string is negative or not
            negative=true;
        }
        int counter =MAXARRAY-1;
        for(int j = str;j >=0;j--){//start at the back of the string
            if(c[j]== '-'){
                number[counter] = (c[j]-'-');//cant hold a '-' in an array of ints
            }else{
                number[counter]= (c[j] -'0');//converts character ascii value to a number
                counter--;
            }
        }
        
        numberlen=MAXARRAY-1-counter;
        this.number=number;//intialize the array of ints
        
    }
    apint(int a){//creates an apint from an int
        String str = String.valueOf(a);//same logic in this method as the constructor with the string
        num=str;
        
        char c[] = str.toCharArray();
        int strlen= c.length-1;
        int[] number= new int[MAXARRAY];
        if(c[0]== '-'){//checks if the string is negative or not
            negative=true;
        }
        int counter =MAXARRAY-1;
        for(int j = strlen;j >=0;j--){//start at the back of the string
            if(c[j]== '-'){
                number[counter] = (c[j]-'-');//cant hold a '-' in an array of ints
            }else{
                number[counter]= (c[j] -'0');//converts character ascii value to a number
                counter--;
            }
        }
        
        numberlen=MAXARRAY-1-counter;
        this.number=number;
    }
    apint(int[] a){//method is used in the factorial function to make a new apint from an array of ints
        
        number=a;
    }
    String print(apint a){//Print method to make the apint look pretty without all the leading zeros
        int[] str = a.getNumber();
        String s = "";//make an empty string
        int counter =0;//counter is used to determine the when the leadings 0s need to be removed
        String zero = "0";
        if(a.Negative()){
            s= s+"-";//add a negative sign to the front of empty string if negative
        }
        while(str[counter]==0){//checks ends when has passed all the leading zeros
            counter++;
            if (counter==MAXARRAY){//if made it to the max array then there is a 0 stored
                return zero;
            }
        }
        for(int i =0+counter;i<MAXARRAY; i++){//starts from counter to maxarray
            s=s+str[i];//add number to the back of string
        }
        return s;


    }
    int getNumLen(){//method to figure out the length of the number
        return numberlen;
    }
    String getNum(){//method to get the string in the class
        return num;
    }
    int[] getNumber(){//method to get the array of ints
        return number;
    }
    boolean Negative(){//determines if int is negative or positive
        return negative;
    }
    apint addition(apint first, apint second){//method to add 2 apints
        int[] a = first.getNumber();
        int[] b = second.getNumber();
        apint sum = new apint();//apint to store the running sum throughout the method
        int[] n = sum.getNumber();
        int carry=0;//used to determine what needs to be carried
        int total=0;//used as a temp to determine int needs to be stored in the array
        int i =MAXARRAY-1;//start at the back of the list to add
        while(i>=0){
            total=a[i]+b[i]+carry;//total is the addition of the 2 numbers including the carry
            n[i]= total%10;//if total is  15 or 25, n[i]=5
            total=total/10;//if total is 15 or 25, total 1,2
            carry= total%10;//carry is now the total mod 10 count
            i--;//decrement i
        }
        return sum;// return the apint of the number
    }
    int[] add(int[] a, int[] b){// method is the same as the addition method except has 
        int[] n = new int[MAXARRAY];//array of int to store the running sum throughout the method
        int carry=0;//used to determine what needs to be carried
        int total=0;//used as a temp to determine int needs to be stored in the array
        int i =MAXARRAY-1;//start at the back of the list to add
        while(i>=0){
            total=a[i]+b[i]+carry;//total is the addition of the 2 numbers including the carry
            n[i]= total%10;//if total is  15 or 25, n[i]=5
            total=total/10;//if total is 15 or 25, total 1,2
            carry= total%10;//carry is now the total mod 10 count
            i--;//decrement i
        }
        return n;//Return the array of ints
    }
    int[] subtract(int[] a, int[] b){//subracts 2 array of ints rather than apints becuase used in methods as a sub method
        int[] n = new int[MAXARRAY];
        int carry=0;
        for(int i=0;i<=MAXARRAY-1;i++){
            if(a[i]>b[i]){//if a is bigger in size
                for(int j = MAXARRAY-1;j >= 0;j--){//start from the back of the array
                    if((a[j]+carry)>=b[j]){//we can just subtract if the top item is larger
                        n[j]=a[j]-b[j]+carry;//subtract and include the carry
                        carry =0;//carry must be 0
                    }
                    else{//if i need to carry and b is bigger than a
                        a[j]=a[j]+10;//add 10 to the top function is equivalent to carrying
                        n[j]=a[j]-b[j]+carry;//then you may subtract
                        carry = -1;//carry a -1 if need to be carried
                        
                    }
                }
                break;//escape the i for loop
            }
            
            
            if(b[i]>a[i]){//if b is bigger in size
                for(int j = MAXARRAY-1;j >= 0;j--){//start from the back of the array
                    if((b[j]+carry)>=a[j]){//subtract the bigger number by smaller one and set to negative
                        n[j]=b[j]-a[j]+carry;//subtract and include the carry
                        carry =0;//carry must be 0
                    }
                    else{//if i need to carry and b is bigger than a
                        b[j]=b[j]+10;//add 10 to the top function is equivalent to carrying
                        n[j]=b[j]-a[j]+carry;//then you may subtract
                        carry = -1;//carry a -1 if need to be carried
                        
                    }
                }
                break;//escape the i for loop
            }
        }
        return n;
    }
    apint subtraction(apint first, apint second){//subracts 2 apints
        int[] a = first.getNumber();
        int[] b = second.getNumber();
        apint difference = new apint();//used to store the difference of the 2 apints
        int[] n = difference.getNumber();
        int carry=0;
        for(int i=0;i<=MAXARRAY-1;i++){
            if(a[i]>b[i]){//if a is bigger in size
                difference.negative=false;//then difference must not be negative
                for(int j = MAXARRAY-1;j >= 0;j--){//start from the back of the array
                    if((a[j]+carry)>=b[j]){//we can just subtract if the top item is larger
                        n[j]=a[j]-b[j]+carry;//subtract and include the carry
                        carry =0;//carry must be 0
                    }
                    else{//if i need to carry and b is bigger than a
                        a[j]=a[j]+10;//add 10 to the top function is equivalent to carrying
                        n[j]=a[j]-b[j]+carry;//then you may subtract
                        carry = -1;//carry a -1 if need to be carried
                        
                    }
                }
                break;//escape the i for loop
            }
            
            
            if(b[i]>a[i]){//if b is bigger in size
                difference.negative = true;//then difference must be negative
                for(int j = MAXARRAY-1;j >= 0;j--){//start from the back of the array
                    if((b[j]+carry)>=a[j]){//subtract the bigger number by smaller one and set to negative
                        n[j]=b[j]-a[j]+carry;//subtract and include the carry
                        carry =0;//carry must be 0
                    }
                    else{//if i need to carry and a is bigger than b
                        b[j]=b[j]+10;//add 10 to the larger function is equivalent to carrying
                        n[j]=b[j]-a[j]+carry;//then you may subtract
                        carry = -1;//carry a -1 if need to be carried
                        
                    }
                }
                break;//escape the i for loop
            }
        }
        return difference;
    }
    int[] shift(int[] a, int b){//used to shift an int array by b elements to b 0s at the end of the array
        int[] temp = new int[MAXARRAY];
        for (int i= MAXARRAY-1;i>=0+b;i--){// start at the back of the array and stop when there are b zeros at the end
            temp[i-b] = a[i];//shifts the data in the temp array
        }
        return temp; //return out shifted data
    }
    int[] append(int[] a, int b){//used to add int b at the end of the list
        int[] temp = new int[MAXARRAY];
        for (int i= MAXARRAY-1;i>=0;i--){//start from the back of the list
            temp[i-1] = a[i];//shift the data in the array of by one
        }
        temp[MAXARRAY-1]=b;// set the last element in the array to b
        return temp;//return our appended data
    }
    apint divide(apint dividend, apint divisor){//solved by counting the amount of subtractions
        int[] a = dividend.getNumber();
        int[] b = divisor.getNumber();
        apint quotient = new apint();//allocate memory for our quotient
        int[] n = quotient.getNumber();
        apint adder = new apint();//used to add or subtract by one
        adder.number[MAXARRAY-1]=1;
        if(dividend.Negative()==divisor.Negative()){//a test for negative a number
            
        }else{
            quotient.negative = true;
        }
        if(dividend.Negative()){//check to see if the dividend is negative or not
            while(dividend.Negative()){//while the dividend is negative
                
                dividend=subtraction(dividend,divisor);//subtract the dividend and divisor
                quotient=addition(quotient,adder);//add one to the quotient since there was a successful subtraction
                for (int i =0;i<=MAXARRAY-1;i++){//check to see if the dividend = 0
                    if(dividend.number[i] != 0){//continue in the while if dividend is not 0
                        break;
                    }else if(i==MAXARRAY-1){//case where it is a perfect divide
                        break;
                        
                    }else if(!dividend.Negative()){// case where there dividend is smaller than the divisor
                        quotient=subtraction(quotient,adder);//subtract one to get the lower bound
                        i=MAXARRAY-1;//need to leave this for loop
                    }
                }
            }
            
        }else if(!dividend.Negative()){//check to see if the dividend is negative or not
            while(!dividend.Negative()){//while the dividend is negative
                
                dividend=subtraction(dividend,divisor);//subtract the dividend and divisor
                quotient=addition(quotient,adder);//add one to the quotient since there was a successful subtraction
                for (int i =0;i<=MAXARRAY-1;i++){//check to see if the dividend = 0
                    if(dividend.number[i] != 0){//continue in the while if dividend is not 0
                        break;
                    }else if(i==MAXARRAY-1){//case where it is a perfect divide
                        break;
                    }else if(dividend.Negative()){// case where there dividend is smaller than the divisor
                        quotient=subtraction(quotient,adder);//subtract one to get the lower bound
                        i=MAXARRAY-1;//need to leave this for loop

                    }
                }
            }
            
        }
        return quotient;
    }
    int[] multi(int[]a,int[]b){//like the multiply fuction but its used in my factorial function
        int[] n = new int[MAXARRAY];
        int carry=0;
        int counter =0;
        int[] total = new int[MAXARRAY];
        for(int j=MAXARRAY-1;j>=0;j--){
            for(int k=MAXARRAY-1;k>=0;k--){
                total[k]=(a[k]*b[j]+carry);//multipy a and b and add carry
                carry = total[k]/10;//carry is total over 10 for example if total is 54 then carry is 5
                total[k]= total[k]%10;//mod by 10 to get rid of the higher order terms
            }
            total=shift(total,MAXARRAY-1-j);//method to know how much to shift data to the left
            n= add(total,n);//add the total of the mulitpy and n is the running total of the whole process
        }
        return n;
    }
    apint multiply(apint first,apint second){
        int[] a = first.getNumber();
        int[] b = second.getNumber();
        apint product = new apint();
        int[] n = product.getNumber();
        int carry=0;
        int counter =0;
        int[] total = new int[MAXARRAY];
        if(first.Negative()==second.Negative()){//test to figure out if product is negative or not
            
        }else{
            product.negative = true;
        }
        for(int i=0;i<=MAXARRAY-1;i++){//loop to figure out which operation goes on top and which goes on the bottom
            if(a[i]>b[i]){//if the first apint element is larger
                for(int j=MAXARRAY-1;j>=0;j--){
                    for(int k=MAXARRAY-1;k>=0;k--){
                        total[k]=(a[k]*b[j]+carry);//multipy a and b and add carry
                        carry = total[k]/10;//carry is total over 10 for example if total is 54 then carry is 5
                        total[k]= total[k]%10;//mod by 10 to get rid of the higher order terms
                    }
                    total=shift(total,MAXARRAY-1-j);//method to know how much to shift data to the left
                    n= add(total,n);//add the total of the mulitpy and n is the running total of the whole process
                }
                product.number = n;
                return product;
            }
            if(b[i]>a[i]){//if the second apint element is larger
                for(int j=MAXARRAY-1;j>=0;j--){
                    for(int k=MAXARRAY-1;k>=0;k--){
                        total[k]=(a[k]*b[j]+carry);//multipy a and b and add carry
                        carry = total[k]/10;//carry is total over 10 for example if total is 54 then carry is 5
                        total[k]= total[k]%10;//mod by 10 to get rid of the higher order terms
                    }
                    total=shift(total,MAXARRAY-1-j);//method to know how much to shift data to the left
                    n= add(total,n);//add the total of the mulitpy and n is the running total of the whole process
                }
                product.number = n;
                return product;
            }
        }
        return product;
    }
    apint factorial(int one){//method to handle 1000! and passes in an int because factorial wont happen with numbers bigger than the int max
        apint alpha = new apint(one);//
        int[] a = alpha.number;
        int[] b = new int[MAXARRAY];
        b[MAXARRAY-1]=1;//used to decrement one to figure out when to stop multiplying

        apint tot = new apint(one);//total starts at one
        int[] total = tot.number;
        
        for(int i=one-2;i>=0;i--){//subtract by 2 becuase you dont need to multiply by one at the end of the factorial function
            a = subtract(a,b);//subtract the count by one
            total = multi(a,total);//multiply the running total and the number in a we are at.
            
        }
        apint fact = new apint(total);// make an apint with total stored in it
        
        return fact;//return the product of the factorial function
    }

}
