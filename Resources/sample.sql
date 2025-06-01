
-- in case i need to restart the database file

CREATE TABLE nodes (
    node_id INTEGER AUTO_INCREMENT NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    z_coord INTEGER NOT NULL,
    label TEXT,
    PRIMARY KEY (node_id)
);
 CREATE TABLE connections (
    connection_id INTEGER AUTO_INCREMENT NOT NULL,
    first_point INTEGER NOT NULL,
    second_point INTEGER NOT NULL,
    label TEXT,
    PRIMARY KEY (connection_id),
    FOREIGN KEY (first_point) REFERENCES nodes(node_id),
    FOREIGN KEY (second_point) REFERENCES nodes(node_id)
);

/*
INSERT INTO nodes (node_id, x_coord, y_coord, z_coord)
VALUES
(0, 13, 16, -18),
(1, 11, -9, -1),
(2, 15, 14, 20),
(3, 18, 16, 1),
(4, 4, 13, 8),
(5, -12, -18, 3),
(6, -6, -20, -4),
(7, 12, 13, 15),
(8, -4, -4, -13),
(9, 0, -9, -13),
(10, -13, -14, 12),
(11, -6, 12, 2),
(12, 20, -4, 2),
(13, 0, -10, 15),
(14, -1, -1, -15),
(15, 8, -11, 0),
(16, 6, -19, 10),
(17, -5, 18, 18),
(18, 15, 19, -14),
(19, 9, 4, 3);
*/
