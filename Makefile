

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -std=c++11
CC = g++
SRC = $(wildcard src/*.cpp)
LDFLAGS= -ldl -lm -L ./lib/libglfw3 -lglfw3
HEADERS = $(wildcard src/*.hpp)
OBJ = $(SRC:%.cpp=%.o)
NAME=scop

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
$(NAME) :  $(OBJ)  $(HEADERS)
	$(CC) $(CFLAGS)  $(OBJ) $(LIBFT) -o $(NAME) $(INC) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re run