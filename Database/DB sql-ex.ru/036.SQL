SELECT DISTINCT Classes.class
FROM Classes INNER JOIN Ships ON (classes.class = ships.name)
UNION
SELECT DISTINCT Classes.class
FROM Classes INNER JOIN Outcomes ON (classes.class = Outcomes.ship)
