SELECT Classes.class, Ships.name, Classes.country
FROM Ships INNER JOIN Classes ON (Classes.class = Ships.class)
WHERE Classes.numGuns >= 10
