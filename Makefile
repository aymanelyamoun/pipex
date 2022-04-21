NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
OBJ = main.o strings/ft_split.o strings/ft_strdup.o strings/ft_strjoin.o strings/ft_strlen.o strings/ft_strncmp.o\
pipex_utils.o cmd_managment.o free_cmds.o pipex_utils_2.o
OBJ_BONUS = main_bonus.o strings/ft_split.o strings/ft_strdup.o strings/ft_strjoin.o strings/ft_strlen.o strings/ft_strncmp.o \
pipex_utils.o cmd_managment.o exec_childs.o here_doc.o free_cmds.o bonus_utils.o pipex_utils_2.o here_doc_utils.o\
get_next_line/get_next_line.o get_next_line/get_next_line_utils.o 

all : $(NAME)

$(NAME) : $(OBJ) pipex.h
	$(CC) $(OBJ) -o $(NAME)
bonus : $(OBJ_BONUS) pipex.h get_next_line/get_next_line.h
	@$(CC) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)
fclean : clean
	@rm -rf $(NAME)
clean_bonus :
	@rm -rf $(OBJ_BONUS)
fclean_bonus : clean_bonus
	@rm -rf $(NAME_BONUS)
re : fclean all