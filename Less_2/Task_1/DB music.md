CREATE TABLE music_genres (
id_genres INTEGER PRIMARY KEY,
name_generes VARCHAR(50)
);

CREATE TABLE music_performer (
id_performer INTEGER PRIMARY KEY,
id_genres INTEGER NOT NULL REFERENCES music_genres(id_genres),
name_performer VARCHAR(50)
);

ALTER TABLE music_genres ADD id_performer INTEGER REFERENCES music_performer(id_performer);

CREATE TABLE album_list (
id_album INTEGER PRIMARY KEY,
id_performer INTEGER NOT NULL REFERENCES music_performer(id_performer),
name_album VARCHAR(50),
realese_year INTEGER
);

ALTER TABLE music_performer ADD id_album INTEGER REFERENCES album_list(id_album);

CREATE TABLE tarck_list (
id_track INTEGER PRIMARY KEY,
id_album INTEGER NOT NULL REFERENCES album_list (id_album),
name_tarck VARCHAR(50),
duration_track TIME
);

CREATE TABLE collection_track (
id_collection INTEGER PRIMARY KEY,
id_track INTEGER NOT NULL REFERENCES track_list (id_track),
id_album INTEGER NOT NULL REFERENCES album_list (id_album),
name_collection VARCHAR(50),
album_release_year DATE
);