--Derrick DeBose
--Query View

--Query statement to make sure I was getting the correct data, used for testing
--SELECT * FROM movies M , earningsView E WHERE M.movieID = E.movieID;

--output before deletions

-- rating | misreportcount 
----------+----------------
-- P      |              1
-- R      |              2
-- G      |              2
--(3 rows)

SELECT M.rating, COUNT(*) AS misreportCount
FROM Movies M, earningsView E
WHERE M.movieID = E.movieID
AND M.year < 2019
AND M.totalEarned<>E.computedEarnings
GROUP BY M.rating;

--2 delete tuples

--This deletes a movie where the movie was made in 2019
DELETE FROM tickets 
where theaterID = 111 
and seatNum = 2 
and showingDate = DATE'2009-06-23' 
and startTime = TIME '11:00:00';

--This deletes a movie where totalEarned<>computedEarnings
--before and after this deletion this movie already
--contributes to the final answer
DELETE FROM tickets 
where theaterID = 444 
and seatNum = 5 
and showingDate = DATE'2020-06-24' 
and startTime = TIME '15:00:00';

--Deletions do not cause outputs to change,
--output after deletions

-- rating | misreportcount 
----------+----------------
-- P      |              1
-- R      |              2
-- G      |              2
--(3 rows)

SELECT M.rating, COUNT(*) AS misreportCount
FROM Movies M, earningsView E
WHERE M.movieID = E.movieID
AND M.year < 2019
AND M.totalEarned<>E.computedEarnings
GROUP BY M.rating;

--Query statement to make sure I was getting the correct data, used for testing
--SELECT * FROM movies M , earningsView E WHERE M.movieID = E.movieID;
