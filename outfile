NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror
OBJ = main.o strings/ft_split.o strings/ft_strdup.o strings/ft_strjoin.o strings/ft_strlen.o strings/ft_strncmp.o pipex_utils.o cmd_managment.o

all : $(NAME)

$(NAME) : $(OBJ) pipex.h
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)