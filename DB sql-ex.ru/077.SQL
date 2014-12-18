WITH T AS (SELECT DISTINCT COUNT(DISTINCT Trip.trip_no) AS CC, Pit.date
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no
WHERE Trip.town_from = 'Rostov'
GROUP BY Trip.town_from, PIT.date)

SELECT CC, date
FROM T
WHERE CC = (SELECT MAX(CC) FROM T)