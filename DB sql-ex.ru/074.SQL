WITH R AS(
SELECT Country, Class
FROM Classes
WHERE Country = 'Russia')

SELECT *
FROM R

UNION

SELECT Country, Class
FROM Classes
WHERE (SELECT COUNT(*) FROM R) = 0