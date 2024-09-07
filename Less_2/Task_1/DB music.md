CREATE TABLE IF NOT EXISTS music_genres(
	id INTEGER PRIMARY KEY,
	name VARCHAR(50) NOT NULL
);
CREATE TABLE IF NOT EXISTS music_performer(
	id INTEGER PRIMARY KEY,
	name VARCHAR(50) NOT NULL
);
CREATE TABLE IF NOT EXISTS album_list(
	id INTEGER PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	realese_year DATE NOT NULL
);
CREATE TABLE IF NOT EXISTS track_list(
	id INTEGER PRIMARY KEY,
	id_album INTEGER REFERENCES album_list(id),
	name VARCHAR(50) NOT NULL,
	duration_track TIME NOT NULL
);
CREATE TABLE IF NOT EXISTS collection(
	id INTEGER PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	realese_year DATE NOT NULL
);
CREATE TABLE IF NOT EXISTS genres_artists (
	id_genre INTEGER REFERENCES music_genres(id),
	id_performer INTEGER REFERENCES music_performer(id),
	CONSTRAINT ganres_perfom_pk PRIMARY KEY(id_genre, id_performer)
);
CREATE TABLE IF NOT EXISTS performer_album (
	id_performer INTEGER REFERENCES music_performer(id),
	id_album INTEGER REFERENCES album_list(id),
	CONSTRAINT aa_pk PRIMARY KEY(id_performer, id_album)
);
CREATE TABLE IF NOT EXISTS collection_track (
	id_collection INTEGER REFERENCES collection(id),
	id_track INTEGER REFERENCES track_list(id),
	CONSTRAINT ct_pk PRIMARY KEY(id_collection, id_track)
);
