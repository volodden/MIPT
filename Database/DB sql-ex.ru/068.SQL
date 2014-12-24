WITH TTT AS (SELECT COUNT(trip_no) AS trip_no
FROM Trip
GROUP BY CASE WHEN town_from > town_to then town_from else town_to END, CASE WHEN town_from > town_to then town_to else town_from END
HAVING COUNT(trip_no) >= ALL (SELECT COUNT(trip_no)
FROM Trip
GROUP BY CASE WHEN town_from > town_to then town_from else town_to END, CASE WHEN town_from > town_to then town_to else town_from END) )

SELECT COUNT(*)
FROM TTT