--Derrick DeBose
--Create a View

CREATE VIEW earnings AS
SELECT S.movieID, sum(ticketPrice) AS computedEarnings
FROM Showings S , Tickets T
WHERE S.theaterID = T.theaterID
AND S.showingDate = T.showingDate
AND S.startTime = T.startTime
GROUP BY S.movieID
HAVING S.movieID IS NOT NULL;

CREATE VIEW temp AS
SELECT DISTINCT movieID 
FROM Movies
WHERE movieID NOT IN (SELECT movieID FROM earnings);

CREATE VIEW earningsView AS
SELECT * 
FROM earnings
UNION
SELECT temp.movieID, 0 AS computedEarnings
FROM temp;

SELECT * FROM earningsView;
