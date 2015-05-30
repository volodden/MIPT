WITH MyT AS (
SELECT PC.price, PC.model, PC.code
FROM PC INNER JOIN Product ON PC.model = Product.model
WHERE Product.maker = 'A'
UNION
SELECT Laptop.price, Laptop.model, Laptop.code
FROM Laptop INNER JOIN Product ON Laptop.model = Product.model
WHERE Product.maker = 'A' )
SELECT AVG(price)
FROM MyT
