--DerricK DeBose
--Lab 2

-- Script file to Create the Movie Theaters DB


-- Create Tables
CREATE TABLE Movies (
movieID Int,
name VARCHAR(30) NOT NULL,
year Int,
rating CHAR(1),
length Int,
totalEarned NUMERIC(7,2),
PRIMARY KEY (movieID),
UNIQUE(name, year)
);

CREATE TABLE Theaters (
theaterID Int,
address VARCHAR(40),
numSeats Int,
PRIMARY KEY (theaterID),
UNIQUE (address)
);

CREATE TABLE TheaterSeats (
theaterID Int,
seatNum Int NOT NULL,
brokenSeat Boolean NOT NULL,
PRIMARY KEY (theaterID, seatNum),
FOREIGN KEY (theaterID) REFERENCES Theaters
);

CREATE TABLE Showings (
theaterID Int,
showingDate DATE,
startTime TIME,
movieID Int,
priceCode CHAR(1),
PRIMARY KEY (theaterID, showingDate, startTime),
FOREIGN KEY (theaterID) REFERENCES Theaters,
FOREIGN KEY (movieID) REFERENCES Movies
);

CREATE TABLE Customers (
customerID Int,
name VARCHAR(30),
address VARCHAR(40),
joinDate DATE,
status char(1),
PRIMARY KEY (customerID),
UNIQUE(name, address)
);

CREATE TABLE Tickets (
theaterID Int,
seatNum Int,
showingDate DATE,
startTime TIME,
customerID Int,
ticketPrice NUMERIC(4,2),
PRIMARY KEY (theaterID, seatNum, showingDate, startTime),
FOREIGN KEY (customerID) REFERENCES Customers,
FOREIGN KEY (theaterID, showingDate, startTime) REFERENCES Showings,
FOREIGN KEY (theaterID, seatNum) REFERENCES TheaterSeats

);

