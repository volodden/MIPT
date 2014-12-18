SELECT model, speed, hd
FROM PC
WHERE ((cd = '12x') OR (cd = '24x')) and (price < 600)
