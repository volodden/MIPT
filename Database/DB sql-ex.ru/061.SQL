WITH X AS (
SELECT NULL AS Out, SUM(Income_o.inc) AS Inc
FROM Income_o
UNION
SELECT SUM(Outcome_o.out), NULL
FROM Outcome_o )

SELECT SUM(Inc)-SUM(Out)
FROM X