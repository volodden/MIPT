SELECT AVG(speed)
FROM PC INNER JOIN Product ON Product.model = PC.model
WHERE (maker = 'A')