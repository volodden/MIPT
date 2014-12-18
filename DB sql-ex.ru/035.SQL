SELECT model, type
FROM Product
WHERE (model NOT LIKE '%[^0-9]%') or (model NOT LIKE '%[^a-zA-Z]%')