WITH MinD AS (SELECT MIN(date) AS date
FROM (SELECT PIT.date, COUNT(DISTINCT Trip.trip_no) as trip
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no
WHERE town_from = 'Rostov' 
GROUP BY PIT.date
HAVING COUNT(DISTINCT Trip.trip_no) >= ALL (SELECT COUNT(DISTINCT Trip.trip_no)
FROM Pass_in_trip AS PIT2 INNER JOIN Trip ON Trip.trip_no = PIT2.trip_no
WHERE town_from = 'Rostov'
GROUP BY PIT2.date)) AS E)

SELECT week.date, CASE WHEN week.date NOT IN (SELECT date FROM Pass_in_trip AS PT INNER JOIN Trip ON Trip.trip_no = PT.trip_no WHERE Trip.town_from = 'Rostov') THEN 0 ELSE (SELECT COUNT (DISTINCT PT.trip_no) FROM Trip INNER JOIN Pass_in_trip AS PT ON Pt.trip_no = Trip.trip_no WHERE Trip.town_from = 'Rostov' and PT.date = week.date) END AS cnt
FROM (SELECT date FROM MinD
UNION SELECT DATEADD(dd, 1, date) FROM MinD
UNION SELECT DATEADD(dd, 2, date) FROM MinD
UNION SELECT DATEADD(dd, 3, date) FROM MinD
UNION SELECT DATEADD(dd, 4, date) FROM MinD
UNION SELECT DATEADD(dd, 5, date) FROM MinD
UNION SELECT DATEADD(dd, 6, date) FROM MinD) AS week