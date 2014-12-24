SELECT (SELECT MIN(trip_no) FROM Trip) AS min1,
(SELECT MIN(trip_no) FROM Trip WHERE trip_no > (SELECT MIN(trip_no) FROM Trip)) AS min2,
(SELECT MIN(trip_no) FROM Trip WHERE trip_no > (SELECT MIN(trip_no) FROM Trip WHERE trip_no > (SELECT MIN(trip_no) FROM TRIP))) AS min3,
(SELECT MAX(trip_no) FROM Trip WHERE trip_no < (SELECT MAX(trip_no) FROM Trip WHERE trip_no < (SELECT MAX(trip_no) FROM TRIP))) AS max3,
(SELECT MAX(trip_no) FROM Trip WHERE trip_no < (SELECT MAX(trip_no) FROM Trip)) AS max2,
(SELECT MAX(trip_no) FROM Trip) AS max1