# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 18:30:43 by hbecki            #+#    #+#              #
#    Updated: 2022/05/30 13:09:29 by hbecki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			builti

HEAD =			./builtins/builtins.h

# GNL_HEAD = get_next_line/get_next_line.h

LIBDIR = 		./libft/

LIBFT = 		libft.a

# CHECKERDIR = 	./checker/

# HEAD_BONUS =	./bonus/pipex_bonus.h

SRC =  builtins/export.c\
		# mandatory/pipex_utils1.c\
		# mandatory/pipex_utils2.c\
		# mandatory/pipex_utils3.c\
		# mandatory/pipex_utils4.c\
		# mandatory/pipex_utils5.c

# SRC_BONUS = bonus/pipex_bonus.c\
# 		bonus/pipex_utils1_bonus.c\
# 		bonus/pipex_utils2_bonus.c\
# 		bonus/pipex_utils3_bonus.c\
# 		bonus/pipex_utils4_bonus.c\
# 		bonus/pipex_utils5_bonus.c



OBJ =			$(SRC:%.c=%.o)



D =				$(SRC:%.c=%.d)



CFLAGS = 		-Wall -Werror -Wextra

CC = 			gcc

RM = 			rm -f

all : 			libmake $(NAME)

$(NAME) : 		$(OBJ) 
				@cp $(LIBDIR)$(LIBFT) .
				$(CC) $(CFLAGS) $(OBJ) libft.a -o $@

libmake :
				@make -C $(LIBDIR)

	
%.o : 			%.c
				$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include 		$(wildcard $(D) $(D_BONUS))


clean:
				@make clean -C $(LIBDIR)
				@$(RM) $(OBJ) $(D) $(D_BONUS) $(OBJ_BONUS) $(OBJ_GNL)

fclean: 		clean
				@$(RM) $(NAME) $(LIBFT)

re: 			fclean all

.PHONY: 		all clean fclean re bonus