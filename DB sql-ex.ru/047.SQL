WITH Q AS(SELECT COUNT(*) AS CNT, PPP.maker
FROM Product AS PPP
GROUP BY PPP.maker)

SELECT COUNT(*) + (SELECT ISNULL(SUM(W.CNT), 0)
FROM Q AS W
WHERE (W.CNT = (SELECT Q.CNT FROM Q WHERE Q.maker = P2.maker) AND W.maker < P2.maker) OR W.CNT > (SELECT Q.CNT FROM Q WHERE Q.maker = P2.maker) 
) AS no,

P2.maker, P2.model
FROM Product AS P1 INNER JOIN Product AS P2 ON (P1.maker = P2.maker AND P1.model <= P2.model)
GROUP BY P2.model, P2.maker