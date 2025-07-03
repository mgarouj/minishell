

# CC      = cc

# CFLAGS  = -Wall -Wextra -Werror
# RL_FLAG = -lreadline 



CC      = cc
READLINE_DIR = $(shell brew --prefix readline)
CFLAGS  = -Wall -Wextra -Werror -I$(READLINE_DIR)/include
RL_FLAG = -L$(READLINE_DIR)/lib -lreadline


SRC     = built/ft_export_3.c built/exporttttt.c built/ft_cd.c built/ft_echo.c built/ft_env.c built/ft_exit.c built/ft_export.c built/ft_fork.c built/ft_pwd.c built/ft_unset.c \
          env_list/export.c env_list/change_env_value.c \
          exc/init_cmd_env.c exc/ex_pipe_utils.c exc/change_in_out.c exc/execute_cmd.c exc/ex_one_cmd.c exc/ex_one_cmd_utils.c exc/ex_pipe_cmd.c exc/find_path.c exc/init_isbuilt.c exc/shlvl_path.c exc/shlvl_path2.c exc/wait_for_child.c \
          libft_fonction/ft_3putstr.c libft_fonction/lib2.c libft_fonction/lib3.c libft_fonction/lib4.c parsing/splitcmd_utils2.c libft_fonction/libf1.c libft_fonction/lib_lst.c \
          parsing/expanding_utils.c parsing/expanding_utils1.c parsing/heredoc.c parsing/expand_heredoc.c parsing/redirec_utils.c parsing/redirections_functions.c parsing/splitcmd_utils.c  parsing/splitcmd_utils1.c parsing/token_utils.c parsing/env.c parsing/expanding.c parsing/synthax_error.c parsing/synthax_utils.c parsing/signals.c parsing/split_cmd.c parsing/token.c \
          utils/split_withe_spaces.c utils/main_utils.c utils/fd_collect.c utils/garbege_collect.c utils/utils.c  utils/utils1.c  utils/utils2.c \
          minishell.c

OBJ     = $(SRC:.c=.o)

NAME    = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(RL_FLAG) -o $(NAME)


%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

