#include <stdio.h> // FILE*
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "raylib.h"
#include "../Include/nodes.h"
#include "../Include/sqlite3.h"

#define ANSI_RED    "\e[31m"
#define ANSI_PURPLE "\e[35m"
#define ANSI_RESET  "\e[0m"

void create_tables(sqlite3 *db) {
        char *tables = 
                "CREATE TABLE nodes ("
                "node_id INTEGER AUTO_INCREMENT NOT NULL, "
                "x_coord INTEGER NOT NULL, "
                "y_coord INTEGER NOT NULL, "
                "z_coord INTEGER NOT NULL, "
                "label VARCHAR(80),"
                "PRIMARY KEY (node_id)"
                ");\n"
                "CREATE TABLE connections ("
                "connection_id INTEGER AUTO_INCREMENT NOT NULL,"
                "first_point INTEGER NOT NULL,"
                "second_point INTEGER NOT NULL,"
                "label VARCHAR(80),"
                "PRIMARY KEY (connection_id),"
                "FOREIGN KEY (first_point) REFERENCES nodes(node_id),"
                "FOREIGN KEY (second_point) REFERENCES nodes(node_id)"
                ");";

        // from zetcode.com example
        char *error_msg = 0;
        int result_pushin = sqlite3_exec(db, tables, 0, 0, &error_msg);
        if (result_pushin != SQLITE_OK) {
                printf(ANSI_RED "temp load-in error: %s\n" ANSI_RESET, error_msg);
                exit(1);
        }
}

sqlite3 *database_open(int argc, char **argv) {
        sqlite3 *db;
        int result = SQLITE_ABORT;
        switch (argc) {
                case 1:
                // open private in-memory
                        result = sqlite3_open(":memory:", &db);
                        printf(ANSI_PURPLE "loading temporary database\n" ANSI_RESET);
                        break;
                case 2:
                        // if we have access to the file and it's a database file
                        int access_result = access(argv[1], R_OK | W_OK);
                        char *p_extension = strrchr(argv[1], '.');
                        if (access_result == -1) {
                                printf(ANSI_RED "%s does not have rw permissions "
                                       "or does not exist\n" ANSI_RESET, argv[1]);
                                exit(0);
                        }
                        if (p_extension == NULL || strcmp(p_extension, ".db")) {
                                printf(ANSI_RED "%s not a database file\n" ANSI_RESET, argv[1]); 
                                exit(0);
                        }

                        result = sqlite3_open(argv[1], &db);
                        printf(ANSI_PURPLE "loading %s\n" ANSI_RESET, argv[1]);
                        break;
                default:
                        printf(ANSI_PURPLE "usage: ./main [\e[4mdatabase.db\e[24m]\n" ANSI_RESET);
                        exit(0);
        }

        if (result != SQLITE_OK) { 
                printf(ANSI_RED "database load error: %s\n" ANSI_RESET, sqlite3_errmsg(db));
                sqlite3_close(db);
                exit(1);
        }
        
        if (argc == 1)
                create_tables(db);
        
        // for velocity, assume that given databases have the template tables

        return db;
}


