import java.sql.*;
import java.io.*;
import java.util.*;

/**
 * A class that connects to PostgreSQL and disconnects.
 * You will need to change your credentials below, to match the usename and password of your account
 * in the PostgreSQL server.
 * The name of your database in the server is the same as your username.
 * You are asked to include code that tests the methods of the MovieTheaterApplication class
 * in a similar manner to the sample RunFilmsApplication.java program.
*/


public class RunMovieTheaterApplication
{
    public static void main(String[] args) {
    	
    	Connection connection = null;
    	try {
    	    //Register the driver
    		Class.forName("org.postgresql.Driver"); 
    	    // Make the connection.
            // You will need to fill in your real username (twice) and password for your
            // Postgres account in the arguments of the getConnection method below.
            connection = DriverManager.getConnection(
                                                     "jdbc:postgresql://cse180-db.lt.ucsc.edu/ddebose",
                                                     "username",
                                                     "password");
            
            if (connection != null)
                System.out.println("Connected to the database!");

            /* Include your code below to test the methods of the MovieTheaterApplication class.
             * The sample code in RunFilmsApplication.java should be useful.
             * That code tests other methods for a different database schema.
             * Your code below: */
            MovieTheaterApplication app = new MovieTheaterApplication(connection);
            /* 
            * Output of getShowingsCount 
            * when the parameter thePriceCode is ‘B’. output is 8
            */
            String priceCodeB = "B";
            Integer b = app.getShowingsCount(priceCodeB);
            System.out.println("When the priceCode is B, getShowingsCount returns: "+ b+"\n");

            /* 
            * Output of updateMovieName when theMovieID is 101 
            * and newMovieName is ‘Avatar 1’: Update is 1. */
            String newName1 = "Avatar 1";
            Integer e = app.updateMovieName(101,newName1);
            System.out.println("When movieID is 101 and movie name is Avatar 1, updateMovieName returns: "+ e+"\n");
            /* 
            * Output of updateMovieName when theMovieID is 888 
            * and newMovieName is ‘Star Wars: A New Hope’: Update is 0. 
            */
            String newName2 = "Star Wars: A New Hope";
            Integer f = app.updateMovieName(888,newName2);
            System.out.println("When movieID is 888 and movie name is Star Wars: A New Hope, updateMovieName returns: "+ f+"\n");

            /* 
            * Output of reduceSomeTicketPrices when maxTicketCount is 15 
            * The answer is: 43. 
            */
            Integer returnVal = app.reduceSomeTicketPrices(15);
            System.out.println("When maxTicketCount is 15, reduceSomeTicketPrices Returns : "+ returnVal+"\n");
            /*
            * Output of reduceSomeTicketPrices when maxTicketCount is 99 
            * The answer is: 76.
            */
            Integer returnVal2 = app.reduceSomeTicketPrices(99);
            System.out.println("When maxTicketCount is 99, reduceSomeTicketPrices Returns :  "+ returnVal2+"\n");



            /*******************
            * Your code ends here */
            
    	}
    	catch (SQLException | ClassNotFoundException e) {
    		System.out.println("Error while connecting to database: " + e);
    		e.printStackTrace();
    	}
    	finally {
    		if (connection != null) {
    			// Closing Connection
    			try {
					connection.close();
				} catch (SQLException e) {
					System.out.println("Failed to close connection: " + e);
					e.printStackTrace();
				}
    		}
    	}
    }
}
