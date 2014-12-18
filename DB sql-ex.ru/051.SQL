WITH T AS(SELECT Ships.name, Classes.numGuns, Classes.displacement
FROM Ships INNER JOIN Classes ON Classes.class = Ships.class
UNION
SELECT Outcomes.ship, Classes.numGuns, Classes.displacement
FROM Outcomes INNER JOIN Classes ON Classes.class = Outcomes.ship)

SELECT Q.name
FROM T AS Q
WHERE Q.numGuns >= ALL (SELECT T.numGuns FROM T WHERE T.displacement = Q.displacement)