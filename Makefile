NAME = minishell

GNL_HEAD = get_next_line/get_next_line.h

SRC = main.c minishell_llist.c minishell_init.c minishell_free_with_str.c minishell_lexer.c minishell_pre_parser.c minishell_parser_next.c \
		minishell_parser.c minishell_lexer_checks.c minishell_utils.c minishell_utils2.c\
		minishell_builtins.c minishell_signals.c minishell_builtins_1.c minishell_builtins_2.c\
		minishell_builtins_3.c minishell_builtins_4.c

SRC_PIPEX =	pipex/mandatory/pipex.c\
	pipex/mandatory/pipex_utils1.c\
	pipex/mandatory/pipex_searchers.c\
	pipex/mandatory/pipex_redirects_and_pipes.c\
	pipex/mandatory/pipex_redirects_and_pipes_1.c\
	pipex/mandatory/pipex_heredoc.c\
	pipex/mandatory/pipex_list_related_funcs.c\
	pipex/mandatory/pipex_parser_for_command.c\
	pipex/mandatory/pipex_free.c\
	pipex/mandatory/pipex_utils5.c

SRC_GNL = get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c

OBJ_GNL = $(SRC_GNL:%.c=%.o)

OBJ_PIPEX = $(SRC_PIPEX:%.c=%.o)

SRC_OBJ = $(SRC:%.c=%.o)

SRC_D = $(SRC:%.c=%.d)

LIBFT = libft.a

CC = cc

CFLAGS = -MD -Wall -Wextra -Werror

FSA =  -g -fsanitize=address

LIBDIR = ./libft/

RM = rm -f

all : libmake $(NAME)


libmake :
				@make -C $(LIBDIR)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ) $(OBJ_PIPEX) $(SRC_GNL)
	@cp $(LIBDIR)$(LIBFT) .
	$(CC) $(SRC_OBJ) $(OBJ_PIPEX) $(SRC_GNL) $(LIBFT) $(FSA) -lreadline -o $@

clean: 
	@make clean -C $(LIBDIR)
	$(RM) $(SRC_OBJ) $(SRC_D) $(OBJ_PIPEX)

fclean: clean
	$(RM) $(NAME)

-include $(SRC_D)

re: fclean all

.PHONY: all clean fclean re