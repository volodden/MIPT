SELECT ISNULL(Income_o.point, Outcome_o.point), ISNULL(Income_o.date, Outcome_o.date), Income_o.inc, Outcome_o.out
FROM Income_o FULL JOIN Outcome_o ON ((Income_o.date = Outcome_o.date) AND (Income_o.point = Outcome_o.point))
