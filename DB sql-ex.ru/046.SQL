SELECT Ships.name, Classes.displacement, Classes.numGuns
FROM Outcomes INNER JOIN Ships ON Outcomes.ship = Ships.name INNER JOIN Classes ON Classes.class = Ships.class
WHERE Outcomes.battle = 'Guadalcanal'

UNION

SELECT Outcomes.ship, Classes.displacement, Classes.numGuns
FROM Outcomes INNER JOIN Classes ON Outcomes.ship = Classes.class
WHERE Outcomes.battle = 'Guadalcanal'

UNION 

SELECT Outcomes.ship, NULL, NULL
FROM Outcomes
WHERE (Outcomes.battle = 'Guadalcanal') AND Outcomes.ship NOT IN
( SELECT Ships.name
FROM Outcomes INNER JOIN Ships ON Outcomes.ship = Ships.name INNER JOIN Classes ON Classes.class = Ships.class
WHERE Outcomes.battle = 'Guadalcanal'

UNION

SELECT Outcomes.ship
FROM Outcomes INNER JOIN Classes ON Outcomes.ship = Classes.class
WHERE Outcomes.battle = 'Guadalcanal'
)
