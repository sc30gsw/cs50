SELECT AVG(r.rating) FROM ratings r 
INNER JOIN movies m 
ON r.movie_id = m.id 
WHERE m.year = '2012';