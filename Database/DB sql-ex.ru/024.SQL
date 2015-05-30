With MyT as (
SELECT Printer.model, Printer.price
FROM Printer
UNION
SELECT PC.model, PC.price
FROM PC
UNION
SELECT Laptop.model, Laptop.price
FROM Laptop )
SELECT model
FROM MyT
WHERE price IN (SELECT MAX(price) FROM MyT)
