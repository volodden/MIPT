SELECT DISTINCT PC1.model, PC2.model, PC1.speed, PC1.RAM
FROM PC AS PC1, PC AS PC2
WHERE (PC1.model > PC2.model) and (PC1.speed = PC2.speed) and (PC1.RAM = PC2.RAM)
