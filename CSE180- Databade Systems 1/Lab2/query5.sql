--Derrick DeBose



--Distinct is not needed because the group by clause allows for no duplicates
SELECT DISTINCT C.customerID, C.name, C.address, Th.address, Th.numSeats, S.priceCode
FROM Customers as C, Tickets as Ti, Theaters as Th, Showings as S
WHERE C.customerID = Ti.customerID
AND Ti.showingDate = S.showingDate
AND Ti.startTime = S.startTime
AND Ti.theaterID = S.theaterID
AND Th.theaterID = Ti.theaterID
AND S.priceCode IS NOT NULL
AND Ti.showingDate >= DATE '06/01/19'
AND Ti.showingDate <= DATE '06/30/19'
AND Th.numSeats > 5
AND C.name LIKE 'D%';
--GROUP BY C.customerID, C.name, C.address, Th.address, Th.numSeats, S.priceCode
--HAVING ;
