
CC := gcc
CFLAGS := -lraylib -Wextra -O1

SRCFILES := Src/main.c Src/aux_camera.c Src/checkpoints.c
INCFILES := Include/aux_camera.h Include/checkpoints.h # just in case

all: $(SRCFILES)
	$(CC) $(SRCFILES) -o main $(CFLAGS)
