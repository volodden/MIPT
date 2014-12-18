SELECT Ships.name
FROM Ships INNER JOIN Classes ON (Ships.class = Classes.class)
WHERE (Classes.bore = 16)
UNION
SELECT Outcomes.ship
FROM Outcomes INNER JOIN Classes ON (Outcomes.ship = Classes.class)
WHERE (Classes.bore = 16)
