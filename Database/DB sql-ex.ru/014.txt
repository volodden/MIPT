SELECT maker, min(type)
FROM PRODUCT
GROUP BY maker
HAVING (count(distinct type) = 1) and (count(model) > 1)
