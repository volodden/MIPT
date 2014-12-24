SELECT Battles.name
FROM Battles
WHERE DATEPART(yyyy, Battles.date) NOT IN (SELECT launched FROM Ships
WHERE launched IS NOT NULL)