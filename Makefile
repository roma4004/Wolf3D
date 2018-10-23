# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2018/10/24 01:32:18 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d


GC = gcc   -O3 -Ipthreads -Wall -Wextra -Werror -framework OpenGL
CM = cmake -O3 -Ipthreads -Wall -Wextra -Werror -framework OpenGL
CL = clang -O3 -Ipthreads -Wall -Wextra -Werror -framework OpenGL

[[ $1 = "clang" ]] && CC=CL || CC=GC
[[ $1 = "cmake" ]] && CC=CM || CC=GC

NORMFLAGS = -R CheckForbiddenSourceHeader

LIBRARY_PATH = library

LFT_PATH = $(LIBRARY_PATH)/libft
SDL_PATH = $(LIBRARY_PATH)/sdl2
TTF_PATH = $(LIBRARY_PATH)/sdl2_ttf
IMG_PATH = $(LIBRARY_PATH)/sdl2_image
MIX_PATH = $(LIBRARY_PATH)/sdl2_mixer

SDL_VER = 2.0.8
TTF_VER = 2.0.14
IMG_VER = 2.0.3
MIX_VER = 2.0.2_3

INC_PATH = include/SDL2
LIB_PATH = lib
SRC_PATH = src

LFT_INC = -I $(LFT_PATH)
SDL_INC = -I $(SDL_PATH)/$(SDL_VER)/$(INC_PATH)
TTF_INC = -I $(TTF_PATH)/$(TTF_VER)/$(INC_PATH)
IMG_INC = -I $(IMG_PATH)/$(IMG_VER)/$(INC_PATH)
MIX_INC = -I $(MIX_PATH)/$(MIX_VER)/$(INC_PATH)

LFT_LNK = -L $(LFT_PATH)
SDL_LNK = -L $(SDL_PATH)/$(SDL_VER)/$(LIB_PATH)
TTF_LNK = -L $(TTF_PATH)/$(TTF_VER)/$(LIB_PATH)
IMG_LNK = -L $(IMG_PATH)/$(IMG_VER)/$(LIB_PATH)
MIX_LNK = -L $(MIX_PATH)/$(MIX_VER)/$(LIB_PATH)

LFT_LNK += -l ft
SDL_LNK += -l SDL2
TTF_LNK += -l SDL2_ttf
IMG_LNK += -l SDL2_image
MIX_LNK += -l SDL2_mixer

ALL_INC = $(SDL_INC) $(TTF_INC) $(IMG_INC) $(MIX_INC) $(LFT_INC)
ALL_LNK = $(SDL_LNK) $(TTF_LNK) $(IMG_LNK) $(MIX_LNK) $(LFT_LNK)

SRC_N = color.c \
        draw.c \
        get_next_line.c \
        interface.c \
        keys.c \
        main.c \
        init.c \
        parser.c

SRC = $(addprefix src/, $(SRC_N))

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(ALL_INC) -c $< -o $@

$(NAME): liball $(OBJ)
	$(CC) $(ALL_INC) $(ALL_LNK) $(OBJ) -o $(NAME)

clean: libclean
	rm -f $(OBJ)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

clang: $(NAME)

cmake: $(NAME)

liball:
	@make -C $(LFT_PATH) all

libclean:
	@make -C $(LFT_PATH) clean

libfclean:
	@make -C $(LFT_PATH) fclean

libre:
	@make -C $(LFT_PATH) re

normall:
	norminette $(NORMFLAGS) ./$(LFT_PATH)/*.c
	norminette $(NORMFLAGS) ./$(LFT_PATH)/*.h
	norminette $(NORMFLAGS) ./$(SRC_PATH)/*.c
	norminette $(NORMFLAGS) ./$(SRC_PATH)/*.h

normsall:
	@norminette $(NORMFLAGS) ./$(LFT_PATH)/*.c # | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) ./$(LFT_PATH)/*.h # | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) ./$(SRC_PATH)/*.c # | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) ./$(SRC_PATH)/*.h # | grep -E '^(Error|Warning)'

normf:
	@norminette $(NORMFLAGS) # | grep -E '^(Error|Warning)'

norm:
	@norminette # | grep -E '^(Error|Warning)'

.phony: all clean fclean re
