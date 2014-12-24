WITH Help AS (SELECT DISTINCT PIT.trip_no, Trip.ID_comp, Trip.time_in, Trip.time_out, PIT.date
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no)

SELECT (SELECT name FROM Company WHERE ID_comp = H.ID_comp) AS Company,

CAST(CAST(SUM(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END) AS NUMERIC(10,2)) / (SELECT COUNT(*) FROM Help WHERE ID_comp = H.ID_comp) AS NUMERIC(10,2)) AS A_Mean,

CAST(EXP(CAST(SUM(LOG(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END)) AS NUMERIC(10,5)) / (SELECT COUNT(*) FROM Help WHERE ID_comp = H.ID_comp)) AS NUMERIC(10,2)) AS G_Mean,

CAST(SQRT(CAST(SUM(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END * CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END) AS NUMERIC(10,2)) / (SELECT COUNT(*) FROM Help WHERE ID_comp = H.ID_comp)) AS NUMERIC(10,2)) AS Q_Mean,

CAST((SELECT COUNT(*) FROM Help WHERE ID_comp = H.ID_comp) / SUM(1 / CAST(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END AS NUMERIC(10,5))) AS NUMERIC(10,2)) AS H_Mean

FROM Help AS H
GROUP BY H.ID_comp

UNION ALL
SELECT 'TOTAL',

CAST(CAST(SUM(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END) AS NUMERIC(10,2)) / (SELECT COUNT(*) FROM Help) AS NUMERIC(10,2)),

CAST(EXP(CAST(SUM(LOG(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END)) AS NUMERIC(10,4)) / (SELECT COUNT(*) FROM Help)) AS NUMERIC(10,2)),

CAST(SQRT(CAST(SUM(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END * CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END) AS NUMERIC(10,2)) / (SELECT COUNT(*) FROM Help)) AS NUMERIC(10,2)),

CAST((SELECT COUNT(*) FROM Help) / SUM(1 / CAST(CASE WHEN time_out > time_in
THEN 24*60 + DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
ELSE DATEPART(hh, time_in)*60 + DATEPART(mi, time_in) - DATEPART(hh, time_out)*60 - DATEPART(mi, time_out)
END AS NUMERIC(10,5))) AS NUMERIC(10,2))
From Help