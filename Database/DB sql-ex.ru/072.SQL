SELECT (SELECT name FROM Passenger WHERE ID_psg = PIT.ID_psg) AS name, COUNT(Trip.trip_no) AS CNT
FROM Trip INNER JOIN Pass_in_trip AS PIT ON Trip.trip_no = PIT.trip_no
GROUP BY PIT.ID_psg
HAVING COUNT(Trip.trip_no) >= ALL (SELECT COUNT(Trip. trip_no)
FROM Trip INNER JOIN Pass_in_trip AS PIT ON Trip.trip_no = PIT.trip_no
GROUP BY PIT.ID_psg
HAVING COUNT (DISTINCT Trip.ID_comp) = 1) AND COUNT(DISTINCT Trip.ID_comp) = 1