.SUFFIXES:
.SECONDARY:
.PHONY: all clean

LDFLAGS=
LIBS=
CFLAGS=-Wall -Werror -g
BIN=army-pokemon

all: $(BIN)

army-pokemon: main.o monster.o army-pokemon.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBS)

main.o: main.c monster.h army.h macro.h
	gcc $(CFLAGS) -o $@ -c $<

monster.o: monster.c monster.h macro.h
	gcc $(CFLAGS) -o $@ -c $<

army-pokemon.o: army-pokemon.c army.h monster.h macro.h
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BIN) *.o *~
 
