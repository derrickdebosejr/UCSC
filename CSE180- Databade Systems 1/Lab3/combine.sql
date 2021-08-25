-- Derrick DeBose
--2.2 Combine Data

BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;

UPDATE Showings
SET movieID = ModifyShowings.movieID
FROM ModifyShowings
WHERE Showings.theaterID = ModifyShowings.theaterID
AND Showings.showingDate = ModifyShowings.showingDate
AND Showings.startTime = ModifyShowings.startTime;

INSERT INTO Showings
SELECT ModifyShowings.theaterID, ModifyShowings.showingDate, ModifyShowings.startTime, ModifyShowings.movieID, NULL
FROM ModifyShowings
WHERE (ModifyShowings.theaterID, ModifyShowings.showingDate, ModifyShowings.startTime)
	NOT IN (SELECT theaterID, showingDate, startTime
			FROM Showings);

COMMIT;
