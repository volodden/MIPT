SELECT maker, model, type
FROM (SELECT TOP ((SELECT COUNT(*) FROM Product)-6) WITH TIES model, maker, type
FROM (SELECT TOP ((SELECT COUNT(*) FROM Product)-3) WITH TIES model, maker, type
FROM Product
ORDER BY model DESC) AS X
ORDER BY model ASC) AS Y