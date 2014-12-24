WITH T AS (SELECT point, date, Outcome, Income
FROM (SELECT point, date, SUM(Outcome) AS Outcome, SUM(Income) AS Income
FROM (SELECT point, date, NULL AS Outcome, SUM(inc) AS Income
FROM Income
Group BY point, date
UNION
SELECT point, date, SUM(out), NULL
FROM Outcome
Group BY point, date) AS X
GROUP BY point, date ) AS Y
WHERE (Outcome IS NULL) OR (Income IS NULL))

SELECT point, date, CASE WHEN Income IS NULL THEN 'out' ELSE 'inc' END operation, CASE WHEN Income IS NULL THEN Outcome ELSE Income END money_sum 
FROM T