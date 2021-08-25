--Derrick DeBose



--DISTINCT is needed because Donald Duck can buy 2 tickets to the same movie.
SELECT DISTINCT M.name, M.year
FROM movies as M, customers as C, tickets as Ti, Showings as S
WHERE C.name = 'Donald Duck'
AND Ti.customerID = C.customerID
AND Ti.theaterID = S.theaterID
AND Ti.showingDate = S.showingDate
AND Ti.startTime = S.startTime
AND S.movieID = M.movieID;
