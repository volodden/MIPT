SELECT Pr1.maker
FROM Product AS Pr1
GROUP BY Pr1.maker
HAVING (SELECT COUNT(*) 
FROM Product
WHERE (Product.type = 'PC') AND (Product.maker = Pr1.maker)) = 
(SELECT COUNT(DISTINCT Product.model)
FROM Product INNER JOIN PC ON Product.model = Pc.model
WHERE (Product.maker = Pr1.maker)
)
AND (SELECT COUNT(*) 
FROM Product
WHERE (Product.type = 'PC') AND (Product.maker = Pr1.maker)) != 0