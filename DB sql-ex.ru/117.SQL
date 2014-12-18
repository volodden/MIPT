WITH T AS (SELECT DISTINCT country, MAX(numGuns)*5000 AS NG, MAX(bore)*3000 AS BR, MAX(displacement) AS DP
FROM Classes AS C
GROUP BY country)

SELECT country, NG AS maxv_val, 'numGuns' AS name
FROM T
WHERE NG >= BR AND NG >= DP

UNION

SELECT country, BR, 'bore'
FROM T
WHERE NG <= BR AND BR >= DP

UNION

SELECT country, DP, 'displacement'
FROM T
WHERE DP >= BR AND NG <= DP