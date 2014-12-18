SELECT (SELECT name FROM Passenger WHERE ID_psg = PIT.ID_psg) AS name, (SELECT SUM(CASE WHEN Trip.time_out > Trip.time_in THEN 24*60 - ABS(DATEDIFF(mi, Trip.time_in, Trip.time_out)) ELSE ABS(DATEDIFF (mi, Trip.time_in, time_out)) END) FROM Pass_in_trip AS P INNER JOIN Trip ON Trip.trip_no = P.trip_no WHERE P.ID_psg = PIT.ID_psg) AS time
FROM Trip INNER JOIN Pass_in_trip AS PIT ON Trip.trip_no = PIT.trip_no
GROUP BY PIT.ID_psg
HAVING COUNT(DISTINCT PIT.place) = COUNT(PIT.place)