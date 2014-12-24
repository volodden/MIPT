SELECT DISTINCT country
FROM Classes
WHERE type = 'bb'

INTERSECT

SELECT DISTINCT country
FROM Classes
WHERE type = 'bc'
