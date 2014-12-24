SELECT DISTINCT Product.type, Product.model, Laptop.speed
FROM Product	INNER JOIN Laptop	ON Product.model = Laptop.model
WHERE Laptop.speed < (	SELECT min(PC.speed) FROM PC )