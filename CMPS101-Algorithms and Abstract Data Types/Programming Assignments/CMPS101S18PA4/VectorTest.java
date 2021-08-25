/*
 * CREATED: Derrick DeBose May 29, 2018
 * CHANGED: May 30, 2018
 */

import java.util.*;
import java.io.*;

// VectorTest.java
// A classes that uses the Vector ADT
// Uses every method that is in the Vector ADT

class VectorTest{
    public static void main(String[] args){
        
        /* Taking the sum of vectors a and b and storing it in sum vector
         */
        Vector a = new Vector(1,2);
        Vector b = new Vector(1,2);
        Vector sum = new Vector();
        System.out.print("Vector a"+a.print()+"+ Vector b"+b.print());
        sum = a.add(b);
        System.out.println("="+sum.print()+"\n");
        
        /* Taking the difference of vectors c and d and storing it in difference vector
         */
        Vector c = new Vector(12,32);
        Vector d = new Vector(31,12);
        Vector difference = new Vector();
        System.out.print("Vector c"+c.print()+"- Vector d"+d.print());
        difference = c.subtract(d);
        System.out.println("="+difference.print()+"\n");
        
        /* Taking the dot product of vector of e and f and store the answer in product
         */
        Vector e = new Vector(2,4);
        Vector f = new Vector(2,4);
        float product = 0;
        System.out.print("Vector e"+e.print()+"dotted with Vector f"+f.print());
        product = e.dotProduct(f);
        System.out.println("= "+product+"\n");
        
        /* Used for the magnitude and angle test using Vector G
         */
        Vector g = new Vector(3,4);
        System.out.println("The vector"+g.print()+"has the magnitude "+g.getMagnitude()+" and the angle "+g.getAngle()+"\n");
        
        /* Used for the polar vector test using the angle and magnitude
         * to find the x,y points for vector h
         */
        Vector h = new Vector();
        float angle = (float)1.8326;
        float magnitude = 11;
        h= Vector.polarVector(angle, magnitude);
        System.out.println("This is the polar vector "+h.print()+" Using the angle "+angle+" and using the magnitude "+magnitude+"\n");
        
        /* The scalar multilpier test takes vector i and multiplies it by 2
         */
        Vector i = new Vector(12,5);
        System.out.print("This vector will be scalar multiplied"+i.print());
        i = i.scalarMultiply(2);
        System.out.println("by a factor of 2 to get"+ i.print()+"\n");
        
        /* The normalize test shows the orginal vector j (x,y) values  with the angle and magnitude
         * Normalized vector j has different (x,y) values with the same angle and magnitude 1.
         */
        Vector j = new Vector(3,4);
        System.out.println("Vector j has the values"+j.print()+
                           "With an angle of "+j.getAngle()+" and magnitude of " +j.getMagnitude());
        j= j.normalize();
        System.out.println("Normalized Vector j has the values"+j.print()+
                           "With an angle of "+j.getAngle()+" and magnitude of " +j.getMagnitude()+"\n");
        
        /* Taking the cross product of vectors k and l and storing the result in vector m
         */
        Vector k = new Vector(2,3);
        Vector l = new Vector(3,4);
        Vector m = new Vector();
        System.out.print("Vector k"+k.print()+"cross producted with Vector l"+l.print()+"\n");
        m = k.crossProduct(l);
        System.out.println("="+m.print());
        
        /* Takes the determinant of vectors o and p and stores the answer in float n
         */
        float n;
        Vector o = new Vector(12,24);
        Vector p = new Vector(2,3);
        n=o.determinant(p);
        System.out.println("The determinant of Vector o"+o.print()+"and Vector p"+p.print()+"="+n+"\n");
    }
}
