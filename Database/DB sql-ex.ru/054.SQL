WITH My AS (SELECT Ships.name, Classes.numGuns
FROM Ships INNER JOIN Classes ON (Ships.class = Classes.class)
WHERE Classes.type = 'bb'
UNION
SELECT Outcomes.ship, Classes.numGuns
FROM Outcomes INNER JOIN Classes ON (Outcomes.ship = Classes.class)
WHERE Classes.type = 'bb' )

SELECT CAST(AVG(CAST(numGuns AS NUMERIC(6, 2))) AS NUMERIC(6, 2))
FROM My