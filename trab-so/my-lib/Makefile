```makefile
# Makefile para my-lib
CPP = g++
CPPFLAGS = -I./include -Wall -ggdb -std=c++23
AR = ar
ARFLAGS = rcs
LIB_NAME = libmy.a
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TEST_SRC = $(wildcard tests/test-*.cpp)
TEST_BINS = $(TEST_SRC:tests/test-%.cpp=test-%)
HEADERS = $(wildcard include/*.h)

all: $(LIB_NAME)
	@echo "My-lib compiled! yes!"

$(LIB_NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

# Alvos de teste (opcionais)
test: $(TEST_BINS)

test-memory-pool: src/memory-pool.cpp tests/test-memory-pool.cpp $(HEADERS)
	$(CPP) -O3 src/memory-pool.cpp tests/test-memory-pool.cpp -o $@ $(CPPFLAGS)

test-timer: tests/test-timer.cpp $(HEADERS)
	$(CPP) tests/test-timer.cpp -o $@ $(CPPFLAGS)

test-event: tests/test-event.cpp $(HEADERS)
	$(CPP) tests/test-event.cpp -o $@ $(CPPFLAGS)

test-any: tests/test-any.cpp $(HEADERS)
	$(CPP) tests/test-any.cpp -o $@ $(CPPFLAGS)

test-bit: tests/test-bit.cpp $(HEADERS)
	$(CPP) tests/test-bit.cpp -o $@ $(CPPFLAGS)

test-math: tests/test-math.cpp $(HEADERS)
	$(CPP) tests/test-math.cpp -o $@ $(CPPFLAGS)

test-matrix: tests/test-matrix.cpp $(HEADERS)
	$(CPP) tests/test-matrix.cpp -o $@ $(CPPFLAGS)

test-interpolation: tests/test-interpolation.cpp $(HEADERS)
	$(CPP) tests/test-interpolation.cpp -o $@ $(CPPFLAGS)

clean:
	-rm -f $(OBJ) $(LIB_NAME) $(TEST_BINS) test-pool-alloc test-stl-alloc

.PHONY: all test clean
```