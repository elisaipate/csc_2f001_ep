.SUFFIXES:
.SECONDARY:
.PHONY: all clean

CXX=g++
LDFLAGS=
LIBS=
CXXFLAGS=-std=c++20 -Wall -Werror -g
BIN=tree
OBJS=main.o

all: $(BIN)

main.o: treemap.h

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) *.o
