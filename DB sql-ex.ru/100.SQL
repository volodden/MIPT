SELECT ISNULL(Ii.date, Oo.date) AS date, ISNULL(Ii.N, Oo.N) AS N, Ii.point, Ii.inc, Oo.point, Oo.out
FROM
(SELECT date, point, (SELECT COUNT(*) FROM Income WHERE Income.date = I.date and Income.code <= I.code) AS N, inc
FROM Income AS I) AS Ii
FULL JOIN
(SELECT date, point, (SELECT COUNT(*) FROM Outcome WHERE Outcome.date = O.date and Outcome.code <= O.code) AS N, out
FROM Outcome AS O) AS Oo ON Ii.date = Oo.date AND Ii.N = Oo.N