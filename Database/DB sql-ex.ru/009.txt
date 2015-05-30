xSELECT DISTINCT Product.maker
FROM Product JOIN PC ON Product.model = PC.model
WHERE speed >= 450
