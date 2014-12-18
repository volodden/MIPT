WITH T AS (SELECT class, COUNT(*) AS CNT
FROM (SELECT DISTINCT ship, class
FROM (SELECT Classes.class, Outcomes.ship, Outcomes.result
FROM Ships INNER JOIN Classes ON Ships.class = Classes.class INNER JOIN Outcomes ON Ships.name = Outcomes.ship
UNION
SELECT  Classes.class, Outcomes.ship, Outcomes.result
FROM Outcomes INNER JOIN Classes ON Outcomes.ship = Classes.class) AS Q
WHERE result = 'sunk') AS W
GROUP BY class)

SELECT *
FROM T
UNION
SELECT class, 0
FROM Classes
EXCEPT
SELECT T.class, 0
FROM T