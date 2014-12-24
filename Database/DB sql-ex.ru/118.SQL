SELECT name, CONVERT(CHAR(10), date, 120) AS battle_dt,

CONVERT(CHAR(10),
(SELECT MIN(Election)
FROM (SELECT CASE
WHEN DATENAME(weekday, firstapril) = 'Monday'
THEN DATEADD(dd, 1, firstapril)
WHEN DATENAME(weekday, firstapril) = 'Tuesday'
THEN DATEADD(dd, 7, firstapril)
WHEN DATENAME(weekday, firstapril) = 'Wednesday'
THEN DATEADD(dd, 6, firstapril)
WHEN DATENAME(weekday, firstapril) = 'Thursday'
THEN DATEADD(dd, 5, firstapril)
WHEN DATENAME(weekday, firstapril) = 'Friday'
THEN DATEADD(dd, 4, firstapril)
WHEN DATENAME(weekday, firstapril) = 'Saturday'
THEN DATEADD(dd, 3, firstapril)
WHEN DATENAME(weekday, firstapril) = 'Sunday'
THEN DATEADD(dd, 2, firstapril) END AS Election

FROM (SELECT DATEADD(dd, 1-DATEPART(dd, YR), DATEADD(mm, 4-DATEPART(mm, YR), YR)) AS firstapril
FROM (SELECT B.date AS YR UNION ALL
SELECT DATEADD(yyyy, 1, B.date) UNION ALL
SELECT DATEADD(yyyy, 2, B.date) UNION ALL
SELECT DATEADD(yyyy, 3, B.date) UNION ALL
SELECT DATEADD(yyyy, 4, B.date) UNION ALL
SELECT DATEADD(yyyy, 5, B.date) UNION ALL
SELECT DATEADD(yyyy, 6, B.date) UNION ALL
SELECT DATEADD(yyyy, 7, B.date) UNION ALL
SELECT DATEADD(yyyy, 8, B.date)) AS NineYears
WHERE (DATEPART(yyyy, YR) % 400 = 0) OR (DATEPART(yyyy, YR) % 4 = 0 AND DATEPART(yyyy, YR) % 100 <> 0)) AS FApr) AS Oooh
WHERE Election >  B.date), 120) AS election_date

FROM Battles AS B