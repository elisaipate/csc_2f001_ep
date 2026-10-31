.SUFFIXES:
.SECONDARY:
.PHONY: all clean

CXX=g++
LDFLAGS=
LIBS=
CXXFLAGS=-std=c++20 -Wall -Werror -g
BIN=bilbao
OBJS=main.o location.o shortest_path.o

all: $(BIN)

main.o location.o: location.h
main.o shortest_path.o: shortest_path.h

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) *.o
