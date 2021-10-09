--Derrick DeBose
--Add General Contraints

ALTER TABLE Tickets
ADD CONSTRAINT positive_TickePrice CHECK(ticketPrice >0);

ALTER TABLE Customers
ADD CONSTRAINT join_Date CHECK (joinDate >= DATE '2015-11-27');

ALTER TABLE Showings
ADD CONSTRAINT not_NULL CHECK(CASE WHEN movieID IS NOT NULL
							  THEN priceCode IS NOT NULL
							  END);
