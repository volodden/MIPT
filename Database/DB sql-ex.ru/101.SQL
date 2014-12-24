WITH New AS (SELECT *, CASE WHEN color = 'n' THEN 1 ELSE 0 END + (SELECT COUNT(color) FROM Printer WHERE code < P.code AND color = 'n') AS G
FROM Printer AS P)

SELECT code, model, color, type, price, (SELECT MAX(model) FROM New WHERE G = N.G) AS max_model, (SELECT COUNT(DISTINCT type) FROM New WHERE G = N.G) AS distct_types, (SELECT AVG(price) FROM New WHERE G = N.G) AS avg_price
FROM New AS N