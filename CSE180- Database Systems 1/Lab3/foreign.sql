--Derrick DeBose
--Add Foreign Key Constraints

ALTER TABLE Tickets
ADD FOREIGN KEY(theaterID, ShowingDate, startTime) REFERENCES Showings
ON UPDATE SET DEFAULT
ON DELETE SET DEFAULT;

ALTER TABLE Tickets
ADD FOREIGN KEY(customerID) REFERENCES Customers
ON DELETE SET NULL
ON UPDATE CASCADE;

ALTER TABLE Tickets
ADD FOREIGN KEY(theaterID, seatNum) REFERENCES TheaterSeats
ON DELETE CASCADE
ON UPDATE CASCADE;
