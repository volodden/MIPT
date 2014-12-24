WITH My AS (SELECT point, date, NULL AS Outcome, SUM(inc) AS Income
FROM Income
Group BY point, date

UNION

SELECT point, date, SUM(out), NULL
FROM Outcome
Group BY point, date )

SELECT point, date, SUM(Outcome) AS Outcome, SUM(Income) AS Income
FROM MY
GROUP BY date, point