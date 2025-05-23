
# note to self: link math lib because C is older than FPU's
CC := gcc
CFLAGS := -lraylib -Wextra -O1 -lm

SRCFILES := Src/main.c Src/camera.c Src/nodes.c
INCFILES := Include/camera.h Include/nodes.h # just in case

all: $(SRCFILES)
	$(CC) $(SRCFILES) -o main $(CFLAGS)
