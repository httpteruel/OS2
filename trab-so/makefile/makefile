# get my-lib:
MYLIB = .

CPP = g++
FLAGS = -std=c++23

# Configurações específicas do ambiente do professor (não usadas no OnlineGDB)
#ifdef CONFIG_TARGET_WINDOWS
#    FLAGS += -DNCURSES_STATIC=1 -DCONFIG_TARGET_WINDOWS=1
#endif
#ifdef CONFIG_TARGET_LINUX
#    FLAGS += -DCONFIG_TARGET_LINUX=1
#endif

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

$(BIN_NAME): $(OBJECTS)
    $(LD) -o $(BIN_NAME) $(OBJECTS) $(LDFLAGS)

clean:
    -$(RM) $(OBJECTS) $(BIN_NAME)