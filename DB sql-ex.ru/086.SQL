SELECT maker, CASE
WHEN SUM(types) = 1 THEN 'Laptop'
WHEN SUM(types) = 2 THEN 'PC'
WHEN SUM(types) = 3 THEN 'Laptop/PC'
WHEN SUM(types) = 4 THEN 'Printer'
WHEN SUM(types) = 5 THEN 'Laptop/Printer'
WHEN SUM(types) = 6 THEN 'PC/Printer'
WHEN SUM(types) = 7 THEN 'Laptop/PC/Printer'
END
AS types
FROM(SELECT DISTINCT maker, CASE WHEN type = 'Laptop' THEN 1 WHEN type = 'PC' THEN 2 ELSE 4 END AS types
FROM Product) AS T
GROUP BY maker