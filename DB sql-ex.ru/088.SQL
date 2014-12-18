/* Невеное решение! Но sql-ex посчитал как правильное!
SELECT (SELECT name FROM Passenger WHERE ID_psg = PIT.ID_psg) AS name, COUNT(PIT.trip_no) AS CNT, (SELECT name FROM Company WHERE ID_comp = MAX(Trip.ID_comp)) AS Company
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no
GROUP BY PIT.ID_psg
HAVING COUNT(DISTINCT Trip.ID_comp) = 1 AND COUNT(PIT.trip_no) >= 4
*/

/* Верное: /*
SELECT (SELECT name FROM Passenger WHERE ID_psg = PIT.ID_psg) AS name, COUNT(PIT.trip_no) AS CNT, (SELECT name FROM Company WHERE ID_comp = MAX(Trip.ID_comp)) AS Company
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no
GROUP BY PIT.ID_psg
HAVING COUNT(DISTINCT Trip.ID_comp) = 1 AND COUNT(PIT.trip_no) >= ALL (SELECT COUNT(PIT.trip_no) AS CNT
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no
GROUP BY PIT.ID_psg
HAVING COUNT(DISTINCT Trip.ID_comp) = 1)