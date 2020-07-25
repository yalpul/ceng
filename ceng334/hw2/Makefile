CC = g++
FLAGS = -Wall -pedantic -std=c++11 -O3 -c -pipe
OUT = Elevator
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
LDFLAGS = -lpthread

all: $(OBJECTS) $(OUT)

release:
	$(CC) -o $(OUT) -O3 -std=c++11 $(SOURCES) $(LDFLAGS)

$(OUT): $(OBJECTS)
	$(CC) -o $(OUT) $(OBJECTS) $(LDFLAGS)
	strip $(OUT)

%.o: %.cpp
	$(CC) $(FLAGS) $<

debug:
	$(CC) -o $(OUT) -DDEBUG -std=c++11 $(SOURCES) $(LDFLAGS) -g

clean:
	rm -rf $(OUT) $(OBJECTS) $(OUT).dSYM
