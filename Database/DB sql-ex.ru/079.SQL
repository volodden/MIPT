SELECT (SELECT name FROM Passenger WHERE ID_psg = PIT.ID_psg) AS name, SUM(CASE WHEN Trip.time_out > Trip.time_in THEN 24*60 - ABS(DATEDIFF(mi, Trip.time_in, Trip.time_out)) ELSE ABS(DATEDIFF (mi, Trip.time_in, time_out)) END) AS time
FROM Trip INNER JOIN Pass_in_trip AS PIT ON PIT.trip_no = Trip.trip_no
GROUP BY PIT.ID_psg
HAVING SUM(CASE WHEN Trip.time_out > Trip.time_in THEN 24*60 - ABS(DATEDIFF(mi, Trip.time_in, Trip.time_out)) ELSE ABS(DATEDIFF (mi, Trip.time_in, time_out)) END) >= ALL (SELECT SUM(CASE WHEN Trip.time_out > Trip.time_in THEN 24*60 - ABS(DATEDIFF(mi, Trip.time_in, Trip.time_out)) ELSE ABS(DATEDIFF (mi, Trip.time_in, time_out)) END) AS time
FROM Trip INNER JOIN Pass_in_trip AS PIT ON PIT.trip_no = Trip.trip_no
GROUP BY PIT.ID_psg)