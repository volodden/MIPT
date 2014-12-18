WITH X AS (SELECT point, date, SUM(inc-out) AS rem
FROM (SELECT point, date, SUM(COALESCE(inc, 0)) AS inc, 0 AS out
FROM Income
GROUP BY point, date
UNION
SELECT point, date, 0, SUM(COALESCE(out, 0))
FROM Outcome
GROUP BY point, date) AS T
GROUP BY point, date)

SELECT point, CONVERT(CHAR(10), date, 103), (SELECT SUM(rem) FROM X WHERE date <= Z.date AND point = Z.point) AS rem
FROM X AS Z