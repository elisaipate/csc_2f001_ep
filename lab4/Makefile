.SUFFIXES:         # remove all the implicit rules (avoid conflicts with our own rules)
.SECONDARY:        # all files are intermediate (keep them, otherwise they are removed)
.PHONY: all clean  # these targets are not files (even if a file named "all" or "clean" exists, the rule is applied)

CXX=g++
LDFLAGS=
LIBS=
CXXFLAGS=-std=c++20 -Wall -Werror -g
BIN=bilbao
OBJS=main.o

all: $(BIN)

# Step 2: link the object files into the binary
$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Step 1: compile each .cpp into an intermediate .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) *.o
