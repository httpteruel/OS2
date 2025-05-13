```makefile
# Makefile para so-sim-cpp-exercicio
MYLIB = ../my-lib
CPP = g++
LD = $(CPP)
FLAGS = -std=c++23 -g
ifdef CONFIG_TARGET_WINDOWS
	FLAGS += -DNCURSES_STATIC=1 -DCONFIG_TARGET_WINDOWS=1
endif
ifdef CONFIG_TARGET_LINUX
	FLAGS += -DCONFIG_TARGET_LINUX=1
endif
CFLAGS = $(FLAGS)
CPPFLAGS = $(FLAGS) -Iinclude -I$(MYLIB)/include -Wall
LDFLAGS = -L$(MYLIB) -lmy -lncurses
BIN_NAME = arq-sim-so
RM = rm
SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h) $(wildcard $(MYLIB)/include/*.h)
OBJS = $(SRC:.cpp=.o)

all: $(BIN_NAME)
	@echo program compiled!
	@echo yes!

$(BIN_NAME): $(OBJS) $(MYLIB)/libmy.a
	$(LD) -o $(BIN_NAME) $(OBJS) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CPP) -c $(CPPFLAGS) $< -o $@

clean:
	-$(RM) $(OBJS) $(BIN_NAME)

.PHONY: all clean
```