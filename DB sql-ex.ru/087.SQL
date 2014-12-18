WITH Info AS (SELECT PIT.ID_psg, Trip.town_from, DATEADD(ss, DATEPART(ss, Trip.time_out), DATEADD(mi, DATEPART(mi, Trip.time_out), DATEADD(hh, DATEPART(hh, Trip.time_out), PIT.date))) AS Time
FROM Pass_in_trip AS PIT INNER JOIN Trip ON PIT.trip_no = Trip.trip_no)

SELECT (SELECT name FROM Passenger WHERE ID_psg = Y.NotMos) AS name, COUNT(*) AS cnt
FROM (SELECT ID_psg AS NotMos
FROM (SELECT ID_psg, town_from, Time
FROM Info AS I
WHERE Time <= ALL (SELECT Time FROM Info WHERE I.ID_psg = ID_psg)) AS X
WHERE town_from <> 'Moscow') AS Y INNER JOIN Pass_in_trip AS PIT2 ON PIT2.ID_psg = Y.NotMos INNER JOIN Trip ON Trip.trip_no = PIT2.trip_no
WHERE Trip.town_to = 'Moscow'
GROUP BY Y.NotMos
HAVING COUNT(*) > 1