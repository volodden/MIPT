SELECT ROW_NUMBER() OVER(ORDER BY maker, CASE WHEN type = 'PC' THEN 1 WHEN type = 'Laptop' THEN 2 ELSE 3 END) AS Nom, 
CASE WHEN type = 'PC' THEN maker
WHEN type = 'Laptop'
THEN CASE
WHEN 'PC' IN (SELECT type FROM Product WHERE maker = T.maker)
THEN ''
ELSE maker
END
ELSE
CASE WHEN 'PC' IN (SELECT type FROM Product WHERE maker = T.maker) OR 'Laptop' IN (SELECT type FROM Product WHERE maker = T.maker)
THEN ''
ELSE maker
END  END AS maker, type
FROM Product AS T
GROUP BY maker, type