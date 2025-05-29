
-- in case i need to restart the database file

CREATE TABLE nodes (
    node_id INTEGER AUTO_INCREMENT NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    z_coord INTEGER NOT NULL,
    PRIMARY KEY (node_id)
);
 CREATE TABLE connections (
    connection_id INTEGER AUTO_INCREMENT NOT NULL,
    first_point INTEGER NOT NULL,
    second_point INTEGER NOT NULL,
    PRIMARY KEY (connection_id),
    FOREIGN KEY (first_point) REFERENCES nodes(node_id),
    FOREIGN KEY (second_point) REFERENCES nodes(node_id)
);

INSERT INTO nodes (x_coord, y_coord, z_coord)
VALUES
(-8, -12, 16),
(-9, 11, -20),
(1, -16, 20),
(-18, 13, 13),
(-17, 3, 10),
(9, -8, -7),
(19, -18, 13),
(-13, 4, 10),
(-16, -8, -4),
(-6, 18, 18),
(-4, 13, -7),
(6, -17, -18),
(-14, -1, -5),
(-16, 10, 20),
(-11, 8, 1),
(16, 1, 12),
(-1, -14, 13),
(8, -13, 3),
(-18, -20, -9),
(19, -6, 2);
