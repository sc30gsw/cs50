SELECT DISTINCT p.name FROM people p 
INNER JOIN stars s
ON p.id = s.person_id
INNER JOIN movies m
ON s.movie_id = m.id
WHERE p.name != 'Kevin Bacon'
AND m.id IN (
  SELECT m.id FROM people p
  INNER JOIN stars s
  ON p.id = s.person_id
  INNER JOIN movies m
  ON s.movie_id = m.id
  WHERE p.name = 'Kevin Bacon'
  AND p.birth = '1958'
);