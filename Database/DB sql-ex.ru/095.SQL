SELECT (SELECT name FROM Company AS A1 WHERE A1.ID_comp = C19.ID_comp) AS company_name,
(SELECT Y.CCC
FROM (SELECT SUM(R.CNT) AS CCC, R.ID_comp
FROM (SELECT COUNT(DISTINCT PIT.trip_no) AS CNT, TR.ID_comp, (SELECT name FROM Company AS A1 WHERE A1.ID_comp = TR.ID_comp) AS company_name, PIT.date
FROM Pass_in_trip AS PIT INNER JOIN Trip AS TR ON PIT.trip_no = TR.trip_no INNER JOIN Company AS CCC ON CCC.ID_comp = TR.ID_comp
GROUP BY TR.ID_comp, PIT.date) AS R
GROUP BY R.ID_comp) AS Y
WHERE Y.ID_comp = C19.ID_comp) AS flights,
COUNT(DISTINCT TR19.plane) AS planes, COUNT(DISTINCT PIT19.ID_psg) AS diff_psngrs,
COUNT(PIT19.ID_psg) as total_psngrs
FROM Pass_in_trip AS PIT19 INNER JOIN Trip AS TR19 ON PIT19.trip_no = TR19.trip_no INNER JOIN Company AS C19 ON TR19.ID_comp = C19.ID_comp
GROUP BY C19.ID_comp