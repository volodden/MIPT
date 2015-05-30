SELECT DISTINCT maker
FROM Product
WHERE (type = 'Printer') and (maker in (SELECT maker
FROM PRODUCT INNER JOIN PC ON PC.model = Product.model
WHERE (PC.speed = (SELECT MAX(speed) FROM PC WHERE PC.ram = (SELECT MIN(ram) FROM PC))) AND (PC.RAM = (SELECT MIN(RAM) FROM PC))))
