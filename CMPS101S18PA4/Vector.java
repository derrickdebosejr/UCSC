/*
 * CREATED: Derrick DeBose May 29, 2018
 * CHANGED: May 30, 2018
 */

import java.util.*;
import java.io.*;

// Vector.java
// A class that implements the Vector ADT.
//
// For this assignment, you must complete this code skeleton.
// You may not change the function prototypes.
// You are expected to fill in the functions to make them work
// as expected, and you can add as much as you need or want.
// We recommend implementing the Vector ADT using x and y coordinates.

// Notes:
// Angles are always in radians, not degrees.

class Vector {

    // Fields
    float x,y,angle,magnitude;

    // Constructors

    // The default constructor should create a new Vector with no magnitude.
    public Vector() {
        x=0;
        y=0;
        magnitude =0;
    }

    // This constructor takes an x and a y coordinate for the Vector.
    public Vector(float x, float y) {
        this.x = x;
        this.y = y;
        //formula for solving angle from x,y points in quadrant 1
        angle = (float)Math.atan(y/x);
        //if vector is in quadrant 4
        if((angle)>(float)(Math.PI)*3/2 ){
            angle = -(angle);
        }
        //if vector is in quadrant 3
        else if((angle)>(float) (Math.PI) ){
            angle = (angle)- (float)Math.PI;
        }
        //if vector is in quadrant 2
        else if((angle)>(float) (Math.PI)/2 ){
            angle = (float)Math.PI -(angle);
        }
        //magnitude is like solving using pythagorean theorem
        magnitude=(float)Math.sqrt((x*x)+(y*y));
    }

    // This "constructor" takes an angle and a magnitude for the Vector.
    // It is not a traditional constructor because only one function can have
    //   the signature Vector(float, float).
    public static Vector polarVector(float angle, float magnitude) {
        //Make a vector to store the x,y values
        Vector v = new Vector();
        //formula for solving for x and y values given an angle and magnitude
        v.x = (float)Math.cos(angle) * magnitude;
        v.y = (float)Math.sin(angle) * magnitude;
        return v;
    }

    // Access functions

    /** getX
     *  Returns the x coordinate of the Vector.
     */
    public float getX() {
        return x;
    }

    /** getY
     *  Returns the y coordinate of the Vector.
     */
    public float getY() {
        return y;
    }

    /** getAngle
     *  Returns the angle of the Vector.
     */
    public float getAngle() {
        return angle;
    }

    /** getMagnitude
     *  Returns the magnitude of the Vector.
     */
    public float getMagnitude() {
        return magnitude;
    }

    /** add
     *  Returns the sum of this Vector with the given Vector.
     */
    public Vector add(Vector other) {
        float otherX = other.getX();
        float otherY = other.getY();
        //add the x's and y's
        other.x = x + otherX;
        other.y = y + otherY;
        return other;
    }

    /** subtract
     *  Returns the difference between this Vector and the given Vector.
     */
    public Vector subtract(Vector other) {
        float otherX = other.getX();
        float otherY = other.getY();
        //subtract the x's and y's
        other.x = x - otherX;
        other.y = y - otherY;
        return other;
    }

    /** dotProduct
     *  Returns the dot product of this Vector and the given Vector.
     */
    public float dotProduct(Vector other) {
        float product;
        float otherX = other.getX();
        float otherY = other.getY();
        //multiply x and y together
        otherX = otherX * x;
        otherY = otherY * y;
        //add the 2 products
        product = otherX + otherY;
        return product;
    }

    /** scalarMultiply
     *  Returns this Vector scaled by the given scalar.
     */
    public Vector scalarMultiply(float scalar) {
        Vector v = new Vector(getX(),getY());
        v.x= v.x * scalar;
        v.y= v.y * scalar;
        return v;
    }

    /** normalize
     *  Returns the normalized version of this Vector, a Vector with the same
     *    angle with magnitude 1.
     */
    public Vector normalize() {
        Vector v = new Vector(getX(),getY());
        float magnitude = v.getMagnitude();
        //divide the x and y by the magnitude
        v.x = v.x / magnitude;
        v.y = v.y / magnitude;
        return v;
    }

    /** Additional functionality
     *  crossProduct
     *  Returns a vector that is the cross product to this Vector and
     *  the given Vector. The cross product is tangent to both.
     *     formula is (ad,-bc) where this Vector is (a,b) and the given Vector is (c,d)
     */
    public Vector crossProduct(Vector other){
        float tempX, tempY;
        
        tempX = other.y * x;
        tempY = other.x * y;
        Vector v = new Vector(tempX, -tempY);
        return v;
    }
    
    /** determinant
     *  Returns a float that is the determinant of this Vector and the given Vector.
     *    formula is ad-bc=determinant where this Vector is (a,b) and the given Vector is (c,d)
     */
    public float determinant(Vector other){
        float tempX, tempY;
        tempX = other.y * x;
        tempY = other.x * y;
        tempX= tempX-tempY;
        return tempX;
    }
    
    /**print
     * Returns a string of this vector as (x,y)
     */
    public String print(){
        return " (" + getX() + ", " + getY() + ") ";
    }


    // Manipulation functions
    // None.  Vectors are immutable.

}
