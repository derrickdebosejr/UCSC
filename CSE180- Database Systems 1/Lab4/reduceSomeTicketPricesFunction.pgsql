CREATE FUNCTION reduceSomeTicketPricesFunction (IN maxTicketCount INTEGER) RETURNS INTEGER AS $$
DECLARE 
	total_dollar_result INTEGER := 0;
	showing_Date DATE;
	start_Time TIME;
	theater_ID INTEGER;
	ticket_Price NUMERIC(4,2);
	price_Code CHAR(1);
	iter INTEGER :=0;


DECLARE the_cursor CURSOR FOR
	SELECT S.theaterID, S.showingDate, S.startTime, S.priceCode, T.ticketPrice
	FROM Showings S, Tickets T
	WHERE S.theaterID = T.theaterID
	AND S.showingDate = T.showingDate
	AND S.startTime = T.startTime
	AND T.ticketPrice IS NOT NULL
	AND S.priceCode IS NOT NULL
	ORDER BY S.priceCode ASC,T.customerID ASC
	FOR UPDATE;

BEGIN

	OPEN the_cursor;
	FETCH FROM the_cursor INTO theater_ID, showing_Date, start_Time, price_Code, ticket_Price;

	WHILE iter < maxTicketCount AND Found
	LOOP
		IF price_Code = 'A' THEN 
			UPDATE Tickets SET ticketPrice = ticket_Price - 3 WHERE CURRENT OF the_cursor;
			total_dollar_result := total_dollar_result + 3;
			iter := iter + 1;
			FETCH FROM the_cursor INTO theater_ID, showing_Date, start_Time, price_Code, ticket_Price;

		ELSEIF price_Code = 'B' THEN 
			UPDATE Tickets SET ticketPrice = ticket_Price - 2 WHERE CURRENT OF the_cursor;
			total_dollar_result := total_dollar_result + 2;
			iter := iter + 1;
			FETCH FROM the_cursor INTO theater_ID, showing_Date, start_Time, price_Code, ticket_Price;

		ELSEIF price_Code = 'C' THEN 
			UPDATE Tickets SET ticketPrice = ticket_Price - 1 WHERE CURRENT OF the_cursor;
			total_dollar_result := total_dollar_result + 1;
			iter := iter + 1;
			FETCH FROM the_cursor INTO theater_ID, showing_Date, start_Time, price_Code, ticket_Price;
		ELSE FETCH FROM the_cursor INTO theater_ID, showing_Date, start_Time, price_Code, ticket_Price;
		END IF;
	END LOOP;

	CLOSE the_cursor;
	RETURN total_dollar_result;
END;
$$ LANGUAGE plpgsql;
