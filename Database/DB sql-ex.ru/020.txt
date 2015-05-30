SELECT maker, count(*)
FROM Product
WHERE (type = 'PC')
GROUP BY maker
HAVING (count(DISTINCT model) >= 3)
