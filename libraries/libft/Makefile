# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/07 12:17:01 by dromanic          #+#    #+#              #
#    Updated: 2018/11/03 18:37:32 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_DIR = ./

BUILDFLAGS = -Wall -Wextra -Werror -std=c99

NORMFLAGS = -R CheckForbiddenSourceHeader

SRC = ft_append_or_new_lst.c \
	ft_atoi.c \
	ft_atol_base.c \
	ft_begin_trim.c \
	ft_bzero.c \
	ft_count_words.c \
	ft_destroy_lst.c \
	ft_digits_len.c \
	ft_end_trim.c \
	ft_free_arr.c \
	ft_get_processors_num.c \
	ft_get_word.c \
	ft_i_atoi.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_lltoa.c \
	ft_lstadd.c \
	ft_lstdel.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_memalloc.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memdel.c \
	ft_memmove.c \
	ft_memset.c \
	ft_num_width.c \
	ft_pow.c \
	ft_putchar.c \
	ft_putchar_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c \
	ft_skip_white_spases.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strclr.c \
	ft_strclrfrom.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strequ.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlen.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strncat.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strnequ.c \
	ft_strnew.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strsplit.c \
	ft_strstr.c \
	ft_strsub.c \
	ft_strtrim.c \
	ft_substr_copy.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_word_len.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -c $(BUILDFLAGS) $(SRC) -I$(INC_DIR)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f ./$(OBJ)

fclean: clean
	@/bin/rm -f ./$(NAME)

normf:
	@norminette $(NORMFLAGS)

norm:
	@norminette

re: fclean all

.phony: all clean fclean re
