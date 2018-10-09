# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/07 12:17:01 by dromanic          #+#    #+#              #
#    Updated: 2018/09/12 12:43:25 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_append_list.c \
	ft_atoi.c \
	ft_atol_base.c \
	ft_begin_trim.c \
	ft_bzero.c \
	ft_destroy_lst.c \
	ft_end_trim.c \
	ft_get_word.c \
	ft_get_processors_num.c \
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
	ft_split_count_str.c \
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
	ft_toupper.c

OBJ = $(SRC:.c=.o)

INC_DIR = ./

COMPFLAGS = -c

BUILDFLAGS = -Wall -Wextra -Werror

LIBFLAGS = -I$(INC_DIR)

NORMFLAGS = -R CheckForbiddenSourceHeader

all: $(NAME)

$(NAME):
	@gcc $(COMPFLAGS) $(SRC) -I./
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f ./*.o

fclean: clean
	@/bin/rm -f ./$(NAME)

normf:
	@norminette $(NORMFLAGS) # | grep -E '^(Error|Warning)'

norm:
	@norminette # | grep -E '^(Error|Warning)'

build:
	@gcc $(BUILDFLAGS) -o $(NAME) $(SRC) -I$(INC_DIR)

buildall:
	@gcc $(BUILDFLAGS) -o $(NAME) *.c -I./*.h

buildlib:
	@gcc $(BUILDFLAGS) -o $(NAME) $(SRC) -L. -lft $(LIBFLAGS) -I./

complib:
	@gcc $(COMPFLAGS) $(SRC) -I./

makelib:
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

re: fclean all
