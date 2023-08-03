CC = g++
CFLAGS = -std=c++2b -Iinclude

# Add your source files here
SRCS = $(wildcard src/*.cpp)

OBJS = $(SRCS:.cpp=.o)

# Name your executable here
MAIN = myproject

.PHONY: all clean test

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(MAIN) $(TEST_OBJS).o test_main

# Test section
TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(TEST_SRCS:.cpp=.o) $(filter-out src/main.o, $(OBJS))
TEST_MAIN = test_main

test: $(TEST_MAIN)

$(TEST_MAIN): $(TEST_OBJS)
	$(CC) $(CFLAGS) -fsanitize=address -o $(TEST_MAIN) $(TEST_OBJS)

