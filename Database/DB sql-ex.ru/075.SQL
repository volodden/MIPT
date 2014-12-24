SELECT Ships.name,
Ships.launched,

CASE 
WHEN Ships.launched IS NULL 
THEN (SELECT MAX(B1.name) FROM Battles AS B1 WHERE B1.date = (SELECT MAX(B2.date) FROM Battles AS B2))

ELSE
CASE
WHEN Ships.launched > (SELECT MAX(B3.date) FROM Battles AS B3)
THEN NULL 

ELSE
(SELECT MAX(B4.name) FROM Battles AS B4 WHERE B4.date = (SELECT MIN(B5.date) FROM Battles AS B5 WHERE DATEPART(yyyy, B5.date) >= Ships.launched)) END END AS battle
FROM Ships