WITH NEWSHIPS AS (SELECT Ships.name, Classes.class
FROM Ships INNER JOIN Classes ON Ships.class = Classes.class
UNION
SELECT Outcomes.ship, Classes.class
FROM Outcomes INNER JOIN Classes ON Outcomes.ship = Classes.class)

SELECT X.class, COUNT(*)
FROM (SELECT class
FROM NEWSHIPS
GROUP BY class
HAVING COUNT(*) > 2) AS X INNER JOIN NEWSHIPS ON NEWSHIPS.class = X.class INNER JOIN Outcomes ON NEWSHIPS.name = Outcomes.ship
WHERE Outcomes.result = 'sunk'
GROUP BY X.class