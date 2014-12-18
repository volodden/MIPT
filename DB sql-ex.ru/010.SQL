SELECT Printer.model, Printer.price
FROM Printer
WHERE price in (
		SELECT MAX(price)
		FROM printer )
