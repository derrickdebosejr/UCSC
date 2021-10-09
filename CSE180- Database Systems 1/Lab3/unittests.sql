--Derrick DeBose
--Write Unit Tests

INSERT INTO Tickets
VALUES (500,1,DATE '2009-06-23',TIME '11:00:00');

INSERT INTO Tickets
VALUES(333,6,DATE '2019-06-23',TIME '20:00:00',5000);

INSERT INTO Tickets
VALUES(222, 3,DATE '2019-06-24', TIME '10:00:00');

UPDATE Tickets
SET ticketPrice = 20;

UPDATE Tickets
SET ticketPrice = -1
WHERE ticketPrice > 0;

UPDATE Customers
SET joinDate = DATE '2019-06-24';

UPDATE Customers
SET joinDate = DATE '2013-06-24';

UPDATE Showings
SET priceCode = 'A'
WHERE movieID = 101;

UPDATE Showings
SET priceCode = NULL
WHERE movieID IS NOT NULL;

