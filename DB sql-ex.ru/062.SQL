WITH X AS (
SELECT NULL AS Out, SUM(Income_o.inc) AS Inc
FROM Income_o
WHERE date < '2001-04-15'
UNION
SELECT SUM(Outcome_o.out), NULL
FROM Outcome_o
WHERE date < '2001-04-15' )

SELECT SUM(Inc)-SUM(Out)
FROM X
