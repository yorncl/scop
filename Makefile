

CFLAGS = -Wall -Wextra -Werror  -g -std=c++11 -fsanitize=address
CC = g++
SRC = $(wildcard src/*.cpp)
LDFLAGS= -lm -L ./lib/libglfw3 -lglfw3 -ldl
HEADERS = $(wildcard src/*.hpp src/*.h)
OBJ = $(SRC:%.cpp=%.o)
NAME=scop
INC= -I ./include

ifeq ($(OS),Windows_NT)
	@echo Build not supported on Windows rip
	exit 1
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDFLAGS += -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
    endif
    ifeq ($(UNAME_S),Darwin)
        LDFLAGS += -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon
    endif
endif

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@  $(INC) $(LDFLAGS)
%/glad.o: %/glad.c
	$(CC) $(CFLAGS) -c $^ -o $@  $(INC)

all : $(NAME)

$(NAME) :  $(OBJ) src/glad.o $(HEADERS)
	$(CC) $(CFLAGS)  $(OBJ) src/glad.o $(LIBFT) -o $(NAME) $(INC) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

42: all
	./$(NAME) ./resources/42.obj
teapot: all
	./$(NAME) ./resources/teapot.obj

.PHONY: all clean fclean re
