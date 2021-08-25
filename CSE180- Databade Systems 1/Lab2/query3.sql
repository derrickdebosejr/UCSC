--Derrick DeBose



--Distinct is not needed because we are comparing all Movies to one movie
--Because movieID is unique for every entry in Movies, we do not need DISTINCT
SELECT M1.movieID, M1.name, M1.year, M1.length
FROM Movies as M1, Movies as M2 
WHERE M2.name = 'Avengers'
AND M2.year = 2011
AND M1.length > M2.length
ORDER BY M1.year desc, M1.name;
