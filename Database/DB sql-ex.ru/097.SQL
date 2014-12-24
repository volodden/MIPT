SELECT code, speed, ram, price, screen
FROM Laptop
WHERE
CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END * 2
<= 
CASE
WHEN speed = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN ram <= price and ram <= screen
THEN ram
WHEN price <= ram and price <= screen
THEN price
ELSE screen
END
WHEN ram = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed <= price and speed <= screen
THEN speed
WHEN price <= speed and price <= screen
THEN price
ELSE screen
END
WHEN price = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed <= ram and speed <= screen
THEN speed
WHEN ram <= speed and ram <= screen
THEN ram
ELSE screen
END
WHEN screen = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed <= ram and speed <= price
THEN speed
WHEN ram <= speed and ram <= price
THEN ram
ELSE price
END
END

and

CASE
WHEN speed = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN ram <= price and ram <= screen
THEN ram
WHEN price <= ram and price <= screen
THEN price
ELSE screen
END
WHEN ram = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed <= price and speed <= screen
THEN speed
WHEN price <= speed and price <= screen
THEN price
ELSE screen
END
WHEN price = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed <= ram and speed <= screen
THEN speed
WHEN ram <= speed and ram <= screen
THEN ram
ELSE screen
END
WHEN screen = CASE
WHEN speed <= ram and speed <= price and speed <= screen
THEN speed
WHEN ram <= speed and ram <= price and ram <= screen
THEN ram
WHEN price <= speed and price <= ram and price <= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed <= ram and speed <= price
THEN speed
WHEN ram <= speed and ram <= price
THEN ram
ELSE price
END
END * 2
<=
CASE
WHEN speed = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN ram >= price and ram >= screen
THEN ram
WHEN price >= ram and price >= screen
THEN price
ELSE screen
END
WHEN ram = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed >= price and speed >= screen
THEN speed
WHEN price >= speed and price >= screen
THEN price
ELSE screen
END
WHEN price = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed >= ram and speed >= screen
THEN speed
WHEN ram >= speed and ram >= screen
THEN ram
ELSE screen
END
WHEN screen = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed >= ram and speed >= price
THEN speed
WHEN ram >= speed and ram >= price
THEN ram
ELSE price
END
END
and
CASE
WHEN speed = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN ram >= price and ram >= screen
THEN ram
WHEN price >= ram and price >= screen
THEN price
ELSE screen
END
WHEN ram = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed >= price and speed >= screen
THEN speed
WHEN price >= speed and price >= screen
THEN price
ELSE screen
END
WHEN price = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed >= ram and speed >= screen
THEN speed
WHEN ram >= speed and ram >= screen
THEN ram
ELSE screen
END
WHEN screen = CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END
THEN CASE
WHEN speed >= ram and speed >= price
THEN speed
WHEN ram >= speed and ram >= price
THEN ram
ELSE price
END
END * 2
<=
CASE
WHEN speed >= ram and speed >= price and speed >= screen
THEN speed
WHEN ram >= speed and ram >= price and ram >= screen
THEN ram
WHEN price >= speed and price >= ram and price >= screen
THEN price
ELSE screen
END