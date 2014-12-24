SELECT Ships.name
FROM Ships INNER JOIN Classes ON Classes.class = Ships.class
WHERE (CASE WHEN Classes.numGuns = 8 THEN 1 ELSE 0 END) +
(CASE WHEN Classes.bore = 15 THEN 1 ELSE 0 END) +
(CASE WHEN Classes.displacement = 32000 THEN 1 ELSE 0 END) +
(CASE WHEN Classes.type = 'bb' THEN 1 ELSE 0 END) +
(CASE WHEN Ships.launched = 1915 THEN 1 ELSE 0 END) +
(CASE WHEN Classes.class = 'Kongo' THEN 1 ELSE 0 END) +
(CASE WHEN Classes.country = 'USA' THEN 1 ELSE 0 END) > 3