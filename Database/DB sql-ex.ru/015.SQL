SELECT DISTINCT HD
FROM PC
GROUP BY HD
HAVING count(*) > 1
