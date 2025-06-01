
# note to self: link math lib because C is older than FPU's
CC := gcc
CFLAGS := -lraylib -lm -Wextra -O1 

SRCFILES := Src/*

all: $(SRCFILES)
	$(CC) $(SRCFILES) -o main $(CFLAGS)
