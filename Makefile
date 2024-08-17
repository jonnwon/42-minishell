# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 14:00:06 by jonchoi           #+#    #+#              #
#    Updated: 2023/05/26 13:39:24 by jonchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
LIBFT			=	libft
LIBFT_HEADER	=	libft.h
LIBFT_LIB		=	$(LIBFT)/libft.a
RDLINE_DIR		=	$(shell brew --prefix readline)

LIBS			=	-lft -L$(LIBFT)/ -lreadline -L$(RDLINE_DIR)/lib

HEADERS			=	-I$(LIBFT) -Iincludes -I$(RDLINE_DIR)/include/
CFLAGS			=	-Wall -Werror -Wextra
#CFLAGS			+=	-g -fsanitize=address

OBJS_DIR		=	objs

SRCS_DIR		=	./src/

B_DIR			=	./builtin/
B_SRC			=	ft_echo.c ft_pwd.c ft_env.c ft_export.c ft_cd.c ft_cd2.c ft_unset.c ft_exit.c\

E_DIR			=	./envp/
E_SRC			=	envp.c envp2.c envp_arr_update.c\

EXEC_DIR		=	./execute/
EXEC_SRC		=	execute.c execute2.c here_doc.c child.c child2.c child3.c set_cmd_nodes.c set_redir.c set_redir2.c\

P_DIR			=	./parsing/
P_SRC			=	parsing.c expander.c expander2.c expander3.c syntax.c make_token.c delete.c set_arr.c merge.c clear_quotes.c\

TREE_DIR		=	./tree/
TREE_SRC		=	set_tree.c tree_utils.c\

U_DIR			=	./utils/
U_SRC			=	utils.c free.c free2.c\

I_DIR			=	./init/
I_SRC			=	init.c check_quotes_paran.c\

#TEST_DIR		=	./test_files/
#TEST_SRC		=	print.c\



SRC				=	main.c\
					$(addprefix $(B_DIR), $(B_SRC))\
					$(addprefix $(E_DIR), $(E_SRC))\
					$(addprefix $(EXEC_DIR), $(EXEC_SRC))\
					$(addprefix $(P_DIR), $(P_SRC))\
					$(addprefix $(TREE_DIR), $(TREE_SRC))\
					$(addprefix $(U_DIR), $(U_SRC))\
					$(addprefix $(I_DIR), $(I_SRC))\
#					$(addprefix $(TEST_DIR), $(TEST_SRC))\

SRCS			=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS			=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

$(NAME) :	$(OBJS) $(LIBFT_LIB)
			@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
			@echo "${GREEN}Minishell has been compiled!${END}"

all		:	$(NAME)

$(LIBFT_LIB):
			@make bonus -C $(LIBFT)

$(OBJS_DIR)/%.o	: 	%.c
			@mkdir -p $(@D)
			@cc $(CFLAGS) -c $^ $(HEADERS) -o $@
			@echo "${YELLOW}Compiling $<${END}"

#clean	:
#			rm -f $(OBJS)
#			make clean -C $(LIBFT)

clean	:
			@rm -rf $(OBJS_DIR)
			@make clean -C $(LIBFT)

fclean	:	
			@make clean
			@rm -f $(NAME)
			@make fclean -C $(LIBFT)
			@echo "${YELLOW}> Cleaning of the Minishell has been done.❌${END}"

re	:		
			@make fclean
			@make all

END		=	$'\x1b[0m
GREEN	=	$'\x1b[32m
YELLOW	=	$'\x1b[33m

.PHONY	:	all clean fclean re
