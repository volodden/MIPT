SELECT Classes.class, ISNULL(MIN(Ships.launched), NULL)
FROM Classes LEFT JOIN Ships ON Classes.class = Ships.class
GROUP BY classes.class
