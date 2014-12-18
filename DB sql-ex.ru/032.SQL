With MY AS (
SELECT Ships.name, Ships.class
FROM Ships
UNION
SELECT Classes.class, Classes.class
FROM Classes INNER JOIN Outcomes ON (Outcomes.ship = Classes.class) )

SELECT Classes.country, CAST(AVG(Classes.bore*Classes.bore*Classes.bore/2) AS NUMERIC(6,2))
FROM MY INNER JOIN Classes ON Classes.class = MY.class
GROUP BY Classes.country