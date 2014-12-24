/* С побитовым операндом */
WITH CTE AS (SELECT Code, Speed, Ram, Speed | Ram AS num_orig, Speed | Ram as working_level, 0 AS cnt
FROM PC

UNION ALL
SELECT Code, Speed, Ram, num_orig, CAST(working_level / 2 AS smallint), CASE WHEN working_level % 2 = 1 THEN cnt+1 ELSE 0 END
FROM CTE
WHERE working_level > 0
)
 
SELECT DISTINCT Code, Speed, Ram
FROM CTE
WHERE cnt = 4

/* Без него
WITH CTE AS (SELECT Code, Speed, Ram, Speed as work1, Ram as work2, 0 AS cnt
FROM PC

UNION ALL

SELECT Code, Speed, Ram, CAST(work1 / 2 AS smallint), CAST(work2 / 2 AS smallint), CASE WHEN work1 % 2 = 1 or work2 % 2 = 1 THEN cnt+1 ELSE 0 END
FROM CTE
WHERE work1 > 0 or work2 > 0
) 

SELECT DISTINCT Code, Speed, Ram
FROM CTE
WHERE cnt = 4
*/