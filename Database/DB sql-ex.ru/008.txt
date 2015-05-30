SELECT DISTINCT Product.maker
FROM Product
WHERE (type = "PC")

EXCEPT

SELECT DISTINCT Product.maker
FROM Product
WHERE (type = "Laptop")
