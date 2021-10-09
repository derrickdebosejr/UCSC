--Derrick DeBose



--Distinct is not needed because we are using the GROUP BY clause on a unique primary key
SELECT DISTINCT C.customerID, C.name
FROM Customers as C, Tickets as T1, Tickets as T2, Showings as S1, Showings as S2
WHERE (C.name LIKE '%a%' OR C.name LIKE '%A%')
AND C.customerID = T1.customerID
AND C.customerID = T2.customerID

AND T1.showingDate = S1.showingDate
AND T1.startTime = S1.startTime
AND T1.theaterID = S1.theaterID

AND T2.showingDate = S2.showingDate
AND T2.startTime = S2.startTime
AND T2.theaterID = S2.theaterID

AND S1.movieID <> S2.movieID;
