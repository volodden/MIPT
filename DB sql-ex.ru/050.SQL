SELECT DISTINCT Outcomes.battle
FROM Outcomes INNER JOIN Ships ON (Outcomes.ship = Ships.name) INNER JOIN Classes ON (Classes.class = Ships.class)
WHERE Classes.class = 'Kongo'
