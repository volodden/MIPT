WITH S AS (
SELECT Classes.country, outcomes.battle
FROM Outcomes INNER JOIN Ships ON Outcomes.ship = Ships.name INNER JOIN Classes ON Ships.class = Classes.class

UNION

SELECT Classes.country, outcomes.battle
FROM Outcomes INNER JOIN Classes ON Outcomes.ship= Classes.class )

SELECT DISTINCT Classes.country, Battles.name
FROM Classes, Battles
WHERE Classes.country NOT IN (SELECT Country
FROM S
WHERE (Classes.country = Country) AND (Battles.name = battle))