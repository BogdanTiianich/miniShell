# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 18:30:43 by hbecki            #+#    #+#              #
#    Updated: 2022/06/22 14:03:04 by hbecki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			pipex.a

HEAD =			./mandatory/pipex.h

GNL_HEAD = get_next_line/get_next_line.h

LIBDIR = 		./libft/

LIBFT = 		libft.a

CHECKERDIR = 	./checker/

HEAD_BONUS =	./bonus/pipex_bonus.h

SRC = pipex/mandatory/pipex.c\
	pipex/mandatory/pipex_utils1.c\
	pipex/mandatory/pipex_utils2.c\
	pipex/mandatory/pipex_utils4.c\
	pipex/pipex_parsers_searchers.c\
	pipex/mandatory/pipex_utils5.c

SRC_BONUS = bonus/pipex_bonus.c\
		bonus/pipex_utils1_bonus.c\
		bonus/pipex_utils2_bonus.c\
		bonus/pipex_utils3_bonus.c\
		bonus/pipex_utils4_bonus.c\
		bonus/pipex_utils5_bonus.c

SRC_GNL = get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c

OBJ =			$(SRC:%.c=%.o)

OBJ_BONUS =		$(SRC_BONUS:%.c=%.o)

OBJ_GNL = $(SRC_GNL:%.c=%.o)

D =				$(SRC:%.c=%.d)

D_BONUS =		$(SRC_BONUS:%.c=%.d)

CFLAGS = 		#-Wall -Werror -Wextra

CC = 			gcc

RM = 			rm -f

all : 			libmake $(NAME)

$(NAME) : 		$(OBJ) $(OBJ_GNL)
				@cp $(LIBDIR)$(LIBFT) .
				ar rcs $(NAME) $?
#				# $(CC) $(CFLAGS) $(OBJ) $(OBJ_GNL) libft.a -o $@

libmake :
				@make -C $(LIBDIR)
checker_make :
				@make -C $(CHECKERDIR)

OBJ_GNL :		$(SRC_GNL) $(GNL_HEAD)
				$(CC) $(CFLAGS) -c $< -o $@	
	
%.o : 			%.c
				$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include 		$(wildcard $(D) $(D_BONUS))

bonus:
				@make OBJ="$(OBJ_BONUS)" HEAD="$(HEAD_BONUS)" all

clean:
				@make clean -C $(LIBDIR)
				@$(RM) $(OBJ) $(D) $(D_BONUS) $(OBJ_BONUS)

fclean: 		clean
				@$(RM) $(NAME) $(LIBFT)

re: 			fclean all

.PHONY: 		all clean fclean re bonus