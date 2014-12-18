SELECT speed, AVG(price)
FROM PC
GROUP BY speed
HAVING speed > 600