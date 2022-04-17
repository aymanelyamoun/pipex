NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror
OBJ = main.o strings/ft_split.o strings/ft_strdup.o strings/ft_strjoin.o strings/ft_strlen.o strings/ft_strncmp.o pipex_utils.o cmd_managment.o
OBJ_bonus = main_bonus.o strings/ft_split.o strings/ft_strdup.o strings/ft_strjoin.o strings/ft_strlen.o strings/ft_strncmp.o pipex_utils.o cmd_managment.o

all : $(NAME)

$(NAME) : $(OBJ) pipex.h
	$(CC) $(OBJ) -o $(NAME)
bonus : $(OBJ_bonus) pipex.h
	$(CC) $(OBJ_bonus) -o pipex_bonus

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)