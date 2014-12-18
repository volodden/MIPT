SELECT chr, value
FROM (SELECT CAST(model AS CHAR(25)) AS model,
CAST(speed AS CHAR(25)) AS speed,
CAST(ram AS CHAR(25)) AS ram,
CAST(hd AS CHAR(25)) AS hd,
CAST(cd AS CHAR(25)) AS cd,
CAST(price AS CHAR(25)) AS price
FROM PC
WHERE code = (SELECT MAX(code) FROM PC)) AS X
UNPIVOT
(value FOR chr IN (model, speed, ram, hd, cd, price)) AS unpvt