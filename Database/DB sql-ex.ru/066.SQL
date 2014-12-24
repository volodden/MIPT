WITH Days AS (SELECT DATEADD(day, a-1, '2003-04-01') AS day
FROM (SELECT 1 AS a UNION SELECT 2 UNION SELECT 3 UNION SELECT 4 UNION SELECT 5 UNION SELECT 6 UNION SELECT 7) AS T)

SELECT Days.day, ISNULL(Days2.Qtv, 0)
FROM Days LEFT JOIN (
SELECT PIT.date, COUNT(DISTINCT PIT.trip_no) AS Qtv
FROM Pass_in_trip AS PIT LEFT JOIN Trip ON Trip.trip_no = PIT.trip_no
WHERE (Trip.town_from = 'Rostov') and (PIT.date >= '2003-04-01') and (PIT.date <= '2003-04-07')
GROUP BY PIT.date) AS Days2 ON Days.day = Days2.date