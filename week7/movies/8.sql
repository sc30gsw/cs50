SELECT p.name FROM people p 
INNER JOIN stars s 
ON p.id = s.person_id 
INNER JOIN movies m 
ON s.movie_id = m.id 
WHERE m.title = 'Toy Story';