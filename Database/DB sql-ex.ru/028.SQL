SELECT AVG(PC.hd)
FROM PC INNER JOIN Product AS My ON PC.model = My.model
WHERE (type = 'PC') AND EXISTS ( SELECT maker
FROM Product
WHERE (type = 'Printer') and (Product.maker = My.maker) )
