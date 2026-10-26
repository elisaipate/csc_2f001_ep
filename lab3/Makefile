.SUFFIXES:
.SECONDARY:
.PHONY: all clean

LDFLAGS=
LIBS=
CFLAGS=-Wall -Werror -g
BIN=army-pokemon army-zombie

all: $(BIN)

army-%: main.o monster.o army-%.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBS)

main.o: main.c monster.h army.h macro.h
	gcc $(CFLAGS) -o $@ -c $<

monster.o: monster.c monster.h macro.h
	gcc $(CFLAGS) -o $@ -c $<

army-pokemon.o: army-pokemon.c army.h monster.h macro.h
	gcc $(CFLAGS) -o $@ -c $<

army-zombie.o: army-zombie.c army.h monster.h macro.h
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BIN) *.o *~
