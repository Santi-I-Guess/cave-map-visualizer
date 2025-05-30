#include <stdio.h> // FILE*
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "raylib.h"
#include "../Include/nodes.h"
#include "../Include/sqlite3.h"

sqlite3 *database_open(int argc, char **argv) {
        sqlite3 *db;
        int result = SQLITE_OK;
        switch (argc) {
        case 1:
                // between ":memory:" and ""
                result = sqlite3_open(":memory:", &db);
                printf("\e[35mloading temporary database\n\e[0m");
                break;
        case 2:
                int result = access(argv[1], R_OK | W_OK);
                if (result == -1) {
                        printf("\e[31m%s does not have rw permissions "
                               "or does not exist\n\e[0m", argv[1]);
                        exit(0);
                }
                char *p_extension = strrchr(argv[1], '.');
                if (p_extension == NULL || strcmp(p_extension, ".db")) {
                        printf("\e[31m%s not a database file\n\e[0m", argv[1]); 
                        exit(0);
                }

                result = sqlite3_open(argv[1], &db);
                printf("\e[35mloading %s\n\e[0m", argv[1]);
                break;
        default:
                printf("\e[35musage: ./main [\e[4mdatabase.db\e[24m]\n\e[0m");
                exit(0);
        }

        if (result != SQLITE_OK) { 
                printf("\e[31mdatabase load error: %s\n\e[0m", sqlite3_errmsg(db));
                sqlite3_close(db);
                exit(1);
        }

        return db;
}
