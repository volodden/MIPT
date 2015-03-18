/* И снова решение с ошибкой! Не работает, когда, например, деньги выдавали 30 дней подряд.
WITH Temp AS(SELECT ISNULL(I.point, O.point) AS point, ISNULL(I.date, O.date) AS date, I.inc, O.out
FROM Income_o AS I FULL JOIN Outcome_o AS O ON I.date = O.date and I.point = O.point)

SELECT T.point, T.date AS DP, CASE WHEN T.out IS NULL THEN T.date ELSE

(SELECT MIN(Day) as Min_Date
FROM
(SELECT DATEADD(dd,n, T.date) AS Day
FROM (SELECT 1 AS n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5
UNION ALL SELECT 6 UNION ALL SELECT 7 UNION ALL SELECT 8 UNION ALL SELECT 9 UNION ALL SELECT 10 UNION ALL SELECT 11 UNION ALL SELECT 12 UNION ALL SELECT 13 UNION ALL SELECT 14 UNION ALL SELECT 15
UNION ALL SELECT 16 UNION ALL SELECT 17 UNION ALL SELECT 18 UNION ALL SELECT 19
UNION ALL SELECT 20 UNION ALL SELECT 21 UNION ALL SELECT 22 UNION ALL SELECT 23
UNION ALL SELECT 24 UNION ALL SELECT 25 UNION ALL SELECT 26 UNION ALL SELECT 27
UNION ALL SELECT 28 UNION ALL SELECT 29 UNION ALL SELECT 30) AS num) as dat
WHERE (dat.Day NOT IN (SELECT date FROM Outcome_o WHERE point = T.point)) AND (DATENAME(weekday, Day) <> 'Sunday'))

END AS DI
FROM Temp AS T
WHERE T.inc IS NOT NULL
*/

/* Универсальное.  */
WITH Temp AS(SELECT ISNULL(I.point, O.point) AS point, ISNULL(I.date, O.date) AS date, I.inc, O.out
FROM Income_o AS I FULL JOIN Outcome_o AS O ON I.date = O.date and I.point = O.point)

SELECT T.point, T.date AS DP, CASE WHEN T.out IS NULL THEN T.date ELSE

(SELECT MIN(Day) as Min_Date
FROM
(SELECT DATEADD(dd, 1, T.date) AS Day
UNION ALL
SELECT DATEADD(dd, 2, T.date)
UNION ALL
SELECT DATEADD(dd, 3, T.date)
UNION ALL
SELECT DATEADD(dd, 1, (SELECT MIN(Temp.date) FROM Temp WHERE date > T.date and DATEADD(dd, 1, Temp.date) NOT IN (SELECT date FROM Outcome_o WHERE point = T.point) and DATENAME(weekday, DATEADD(dd, 1, date)) <> 'Sunday'))
) as dat
WHERE (dat.Day NOT IN (SELECT date FROM Outcome_o WHERE point = T.point)) AND (DATENAME(weekday, Day) <> 'Sunday'))

END AS DI
FROM Temp AS T
WHERE T.inc IS NOT NULL