SELECT DISTINCT Product.maker, AVG(PC.hd)
FROM Product INNER JOIN PC ON PC.model = Product.model
WHERE Product.maker in (SELECT maker FROM Product WHERE type = 'printer')
GROUP BY Product.maker