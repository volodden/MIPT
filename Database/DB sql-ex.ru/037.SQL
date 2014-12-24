SELECT My.class
FROM ( SELECT Classes.*, Ships.name
FROM Classes INNER JOIN Ships ON (Classes.class = Ships.class)
UNION
SELECT Classes.*, Outcomes.ship
FROM Classes INNER JOIN Outcomes ON (Classes.class = Outcomes.ship) ) AS My
GROUP BY class
HAVING count(*) = 1
