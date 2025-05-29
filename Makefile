
# note to self: link math lib because C is older than FPU's
CC := gcc
CFLAGS := -lraylib -lm -Wextra -O1 

SRCFILES := Src/main.c Src/camera.c Src/nodes.c
INCFILES := Include/camera.h Include/nodes.h # just in case

all: $(SRCFILES)
	$(CC) $(SRCFILES) Include/sqlite3.o -o main $(CFLAGS)
