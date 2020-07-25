CC = g++
OUT = hw3
SRCS = $(wildcard *.cpp)
OBJECTS = $(SRCS:%.cpp=%.o)
FLAGS = -O3 -march=native -std=c++11 -Wall -pedantic -pipe

all: $(OBJECTS) $(OUT) 

$(OUT): $(OBJECTS)
	$(CC) -o $(OUT) $(FLAGS) $(OBJECTS)
	strip $(OUT)

%.o: %.cpp
	$(CC) -c $(FLAGS) $<

clean:
	rm -f $(OBJECTS) $(OUT)
