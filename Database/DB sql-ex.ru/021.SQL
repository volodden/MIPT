SELECT Product.maker, MAX(PC.price)
FROM Product INNER JOIN PC ON PC.model = Product.model
GROUP BY maker
HAVING (count(*) > 0)
