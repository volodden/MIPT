SELECT DISTINCT My1.ship
FROM Outcomes AS My1 INNER JOIN Battles AS My2 ON (My2.name = My1.battle)
WHERE (My1.result = 'damaged') AND EXISTS ( SELECT Outcomes.ship
FROM Outcomes INNER JOIN Battles ON (Battles.name = Outcomes.battle)
WHERE (My1.ship = Outcomes.ship) AND (Battles.date > My2.date) )
