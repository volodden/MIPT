SELECT DISTINCT Ships.name
FROM Ships INNER JOIN Classes ON Ships.class = Classes.class
WHERE (isnull(Ships.launched,0 )>= 1922) AND (classes.displacement > 35000) AND (Classes.type = 'bb')
