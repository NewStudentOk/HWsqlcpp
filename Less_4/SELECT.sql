--Задание 2
--Название и продолжительность самого длительного трека.

SELECT name, duration_track 
FROM track_list
ORDER BY duration_track DESC  
LIMIT 1;

--Название треков, продолжительность которых не менее 3,5 минут.

SELECT name, duration_track 
FROM track_list
WHERE duration_track > '00:03:30'
ORDER BY duration_track DESC

--Названия сборников, вышедших в период с 2018 по 2020 годы включительно.

SELECT name, realese_year
FROM collection
WHERE realese_year BETWEEN '2018-01-01' AND '2020-01-01'
ORDER BY realese_year DESC  

--Исполнители, чьё имя состоит из одного слова.

SELECT name
FROM music_performer
WHERE name NOT LIKE '% %'; 

--Название треков, которые содержат слова «мой» или «my».

SELECT name
FROM track_list
WHERE name ilike '%мой%' OR name ilike '%my%'

--Задание 3

--Количество исполнителей в каждом жанре.

SELECT name_genres, COUNT(*) FROM music_genres mg
JOIN genres_artists ga ON ga.id_genre = mg.id 
JOIN music_performer mp ON ga.id_performer = mp.id 
GROUP BY name_genres;

--Количество треков, вошедших в альбомы 2019–2020 годов.

SELECT COUNT(*) FROM track_list tl
JOIN album_list al ON tl.id_album = al.id  
WHERE al.realese_year BETWEEN '2019-01-01' AND '2020-01-01'
GROUP BY ROLLUP(name_track)
ORDER BY name_track DESC
LIMIT 1;

--Средняя продолжительность треков по каждому альбому.

SELECT al.name_album, AVG(duration_track) FROM track_list tl 
JOIN album_list al ON tl.id_album = al.id 
GROUP BY al.name_album 

--Все исполнители, которые не выпустили альбомы в 2020 году.

SELECT mp.id, mp.name_performer
FROM music_performer mp
WHERE NOT EXISTS (
    SELECT 1
    FROM performer_album pa
    INNER JOIN album_list al ON pa.id_album = al.id
    WHERE pa.id_performer = mp.id AND al.realese_year = '01-01-2020'
);

--Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами).

SELECT name_performer, al.name_album FROM music_performer mp
JOIN performer_album pa ON pa.id_performer = mp.id
JOIN album_list al ON al.id = pa.id_album 
WHERE name_performer  ilike 'Исполнитель'
GROUP BY name_performer, al.name_album ;


--Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами
SELECT name_performer, al.name_album FROM music_performer mp
JOIN performer_album pa ON pa.id_performer = mp.id
JOIN album_list al ON al.id = pa.id_album 
WHERE name_performer  ilike 'Исполнитель'
GROUP BY name_performer, al.name_album;
