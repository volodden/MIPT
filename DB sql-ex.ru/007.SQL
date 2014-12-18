SELECT DISTINCT Pc.model, PC.price
FROM Product JOIN PC ON Product.model = PC.model
WHERE (Product.maker = 'B') AND (Product.type = 'PC')

UNION

SELECT DISTINCT Printer.model, Printer.price
FROM Product JOIN Printer ON Product.model = Printer.model
WHERE (Product.maker = 'B') AND (Product.type = 'Printer')

UNION

SELECT DISTINCT Laptop.model, Laptop.price
FROM Product JOIN Laptop ON Product.model = Laptop.model
WHERE (Product.maker = 'B') AND (Product.type = 'Laptop')
