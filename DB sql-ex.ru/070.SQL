WITH T AS (SELECT Battle, Country, COUNT(ship) AS CS
FROM (
SELECT Outcomes.battle, Classes.country, Outcomes.ship
FROM Outcomes INNER JOIN Ships ON Outcomes.ship = Ships.name INNER JOIN Classes ON Classes.class = Ships.class

UNION

SELECT Outcomes.battle, Classes.country, Outcomes.ship
FROM Outcomes INNER JOIN Classes ON Outcomes.ship = Classes.class ) AS X
GROUP BY Battle, Country )

SELECT DISTINCT battle
FROM T
WHERE CS >= 3