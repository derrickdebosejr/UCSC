--Derrick DeBose



--DISTINCT is needed because every broken seat will get returned and
--Theaters that have more than one broken seats will get printed twice.
SELECT DISTINCT T.theaterID, T.address
FROM Theaters as T, TheaterSeats as TS
WHERE TS.brokenSeat = TRUE
AND T.theaterID = TS.theaterID;
