# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/14 20:47:51 by jonchoi           #+#    #+#              #
#    Updated: 2023/04/19 09:11:52 by jonchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= cc
CFLAG	= -Wall -Wextra -Werror

RM		= rm
RMFLAG = -f

AR		= ar
ARFLAG = -crs


SRCS_1	= ft_isalpha.c		\
		  ft_isdigit.c		\
		  ft_isalnum.c		\
		  ft_isascii.c		\
		  ft_isprint.c		\
		  ft_strlen.c		\
		  ft_memset.c		\
		  ft_bzero.c		\
		  ft_memcpy.c		\
		  ft_memmove.c		\
		  ft_strlcpy.c		\
		  ft_strlcat.c		\
		  ft_strncmp.c		\
		  ft_toupper.c		\
		  ft_tolower.c		\
		  ft_strchr.c		\
		  ft_strrchr.c		\
		  ft_memchr.c		\
		  ft_memcmp.c		\
		  ft_strnstr.c		\
		  ft_atoi.c			\
		  ft_calloc.c		\
		  ft_strdup.c		\


SRCS_2	= ft_substr.c		\
		  ft_strjoin.c		\
		  ft_strtrim.c		\
		  ft_split.c		\
		  ft_itoa.c			\
		  ft_strmapi.c		\
		  ft_striteri.c		\
		  ft_putchar_fd.c	\
		  ft_putstr_fd.c	\
		  ft_putendl_fd.c	\
		  ft_putnbr_fd.c	\


SRCS	= $(SRCS_1)			\
		  $(SRCS_2)			\

OBJS	= $(SRCS:.c=.o)



SRCS_BN = ft_lstnew.c		\
		  ft_lstadd_front.c	\
		  ft_lstsize.c		\
		  ft_lstlast.c		\
		  ft_lstadd_back.c	\
		  ft_lstdelone.c	\
		  ft_lstclear.c		\
		  ft_lstiter.c		\
		  ft_lstmap.c		\


OBJS_BONUS = $(SRCS_BN:.c=.o)

ifdef WITH_B
	OBJECTS = $(OBJS) $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJECTS)
	@$(AR) $(ARFLAG) $@ $^

%.o : %.c
	@$(CC) $(CFLAG) -c $< -o $@

clean :
	@$(RM) $(RMFLAG) $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(RM) $(RMFLAG) $(NAME)

re : fclean all


bonus : 
	@make WITH_B=1 all

.PHONY : all clean fclean re bonus
