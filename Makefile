# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2018/10/10 13:40:00 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

GC = gcc -O3 -Ipthreads -Wall -Wextra -Werror
CM = cmake -O3 -Ipthreads -Wall -Wextra -Werror
CL = clang -O3 -Ipthreads -Wall -Wextra -Werror

[[ $1 = "clang" ]] && CC=CL || CC=GC
[[ $1 = "cmake" ]] && CC=CM || CC=GC

LIBKEYS = -framework OpenGL \
        -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
        -F ~/Library/Frameworks/ -framework SDL2 \
        -I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
        -F ~/Library/Frameworks/ -framework SDL2_image \
        -I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers \
        -F ~/Library/Frameworks/ -framework SDL2_ttf \
        -I ~/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers \
        -F ~/Library/Frameworks/ -framework SDL2_mixer\
        -framework SDL2 -rpath ~/Library/Frameworks/SDL2.framework/

        #-F /Library/Frameworks -framework SDL2 \
        #-I /Library/Frameworks/SDL2.framework/Headers \
        #-F /Library/Frameworks/ -framework SDL2 \
        #-I./library/frameworks/SDL2_ttf.framework/Headers \
        #-F./library/frameworks/SDL2_ttf.framework -framework SDL2_ttf \
        #-I./library/frameworks/SDL2_image.framework/Headers \
        #-F./library/frameworks/ -framework SDL2_image \
        #-I./library/frameworks/SDL2_mixer.framework/Headers \
        #-F./library/frameworks/ -framework SDL2_mixer \

SRC_N = main.c init.c interface.c

SRC = $(addprefix src/, $(SRC_N))

OBJ = $(SRC:.c=.o)

LIBS = library/libft/libft.a

all: $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME): liball $(OBJ)
	$(CC) $(LIBKEYS) $(OBJ) $(LIBS) -o $(NAME)

clean: libclean
	rm -f $(OBJ)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

clang: $(NAME)

cmake: $(NAME)

liball:
	@make -C library/libft/ all

libclean:
	@make -C library/libft/ clean

libfclean:
	@make -C library/libft/ fclean

libre:
	@make -C library/libft/ re

.phony: all clean fclean re