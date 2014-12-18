SELECT DISTINCT Product.maker, Printer.price
FROM Product INNER JOIN Printer ON Product.model = Printer.model
WHERE (price IN (SELECT MIN(price) FROM Printer WHERE color = 'y')) AND (color = 'y')