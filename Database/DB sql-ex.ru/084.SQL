SELECT (SELECT name FROM Company WHERE ID_comp = Trip.ID_comp) AS name,
SUM(CASE WHEN DATEPART(dd, date) >= 1 AND DATEPART(dd, date) <= 10 THEN 1 ELSE 0 END) AS '1-10',
SUM(CASE WHEN DATEPART(dd, date) >= 11 AND DATEPART(dd, date) <= 20 THEN 1 ELSE 0 END) AS '11-20',
SUM(CASE WHEN DATEPART(dd, date) >= 21 AND DATEPART(dd, date) <= 30 THEN 1 ELSE 0 END) AS '21-30'
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no
WHERE CONVERT(CHAR(7), PIT.date, 120) = '2003-04'
GROUP BY Trip.ID_comp