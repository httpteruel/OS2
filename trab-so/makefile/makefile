# get my-lib:
MYLIB = .

CPP = g++
FLAGS = -std=c++23

CFLAGS = $(FLAGS)
CPPFLAGS = $(FLAGS) -I$(MYLIB)/include -Wall
LDFLAGS =  # Removido -lncurses, não necessário
BIN_NAME = trab-so
RM = rm

########################################################

SRC = $(wildcard src/*.cpp)

headerfiles = $(wildcard include/*.h)

OBJS = ${SRC:.cpp=.o}

########################################################

# implicit rules

%.o : %.cpp $(headerfiles)
	$(CPP) -c $(CPPFLAGS) $< -o $@

########################################################

all: $(BIN_NAME)
	@echo program compiled!
	@echo yes!

$(BIN_NAME): $(OBJS)
	$(CPP) -o $(BIN_NAME) $(OBJS) $(LDFLAGS)

clean:
	-$(RM) $(OBJS) $(BIN_NAME)