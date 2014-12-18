SELECT (SELECT name FROM Passenger WHERE  ID_psg = P.ID_psg)
FROM (SELECT PIT.ID_psg, Trip.town_from AS Town
FROM Pass_in_trip AS PIT INNER JOIN Trip ON PIT.trip_no = Trip.trip_no
GROUP BY PIT.ID_psg, Trip.town_from

UNION

SELECT PIT.ID_psg, Trip.town_to
FROM Pass_in_trip AS PIT INNER JOIN Trip ON PIT.trip_no = Trip.trip_no
GROUP BY PIT.ID_psg, Trip.town_to) AS X INNER JOIN Passenger AS P ON X.ID_psg = P.ID_psg
GROUP BY P.ID_psg
HAVING COUNT(DISTINCT TOWN) = 2