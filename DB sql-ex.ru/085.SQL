SELECT maker
FROM(SELECT maker, MAX(type) AS type, COUNT(DISTINCT model) AS model
FROM Product
GROUP BY maker
HAVING COUNT(DISTINCT type) = 1) AS X
WHERE (type = 'Printer') OR (model > 2 AND type = 'PC')