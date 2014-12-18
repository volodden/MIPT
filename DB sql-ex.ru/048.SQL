SELECT CLasses.class
FROM Outcomes FULL JOIN Ships ON (Outcomes.ship = Ships.name) INNER JOIN Classes ON (Ships.class = Classes.class)
WHERE (Outcomes.result = 'sunk') AND (Classes.class IS NOT NULL)
UNION
SELECT CLasses.class
FROM Outcomes FULL JOIN Classes ON (Outcomes.ship = Classes.class)
WHERE (Outcomes.result = 'sunk') AND (Classes.class IS NOT NULL)
