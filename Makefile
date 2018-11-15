# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2018/11/14 21:30:45 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

СC = gcc   -O3 -Ipthreads -Wall -Wextra -Werror
CM = cmake -O3 -Ipthreads -Wall -Wextra -Werror
CL = clang -O3 -Ipthreads -Wall -Wextra -Werror

[[ $1 = "clang" ]] && CC=CL
[[ $1 = "cmake" ]] && CC=CM

NORMFLAGS = -R CheckForbiddenSourceHeader
PROJ_LIB_PATH = libraries
PROJ_SRC_PATH = sources
PROJ_INC_PATH = includes
PROJ_OBJ_PATH = objectives
SDL2_INC_PATH = Headers

#start sdl2.frameworks section

#LFT_LIB_NAME = libft
#SDL_LIB_NAME = SDL2.framework
#TTF_LIB_NAME = SDL2_ttf.framework
#IMG_LIB_NAME = SDL2_image.framework
#MIX_LIB_NAME = SDL2_mixer.framework
#
#SDL_FW = -framework $(SDL_LIB_NAME)
#TTF_FW = -framework $(TTF_LIB_NAME)
#IMG_FW = -framework $(IMG_LIB_NAME)
#MIX_FW = -framework $(MIX_LIB_NAME)
#
#LFT_PATH = $(PROJ_LIB_PATH)/$(LFT_LIB_NAME)
#SDL_PATH = $(PROJ_LIB_PATH)/$(SDL_LIB_NAME)
#TTF_PATH = $(PROJ_LIB_PATH)/$(TTF_LIB_NAME)
#IMG_PATH = $(PROJ_LIB_PATH)/$(IMG_LIB_NAME)
#MIX_PATH = $(PROJ_LIB_PATH)/$(MIX_LIB_NAME)
#
#PRJ_INC = -I $(PROJ_INC_PATH)
#LFT_INC = -I $(LFT_PATH)
#SDL_INC = -I $(SDL_PATH)/$(SDL2_INC_PATH)
#TTF_INC = -I $(TTF_PATH)/$(SDL2_INC_PATH)
#IMG_INC = -I $(IMG_PATH)/$(SDL2_INC_PATH)
#MIX_INC = -I $(MIX_PATH)/$(SDL2_INC_PATH)

#end sdl2.frameworks section

#start sdl2 section (with brew installed library)

SDL2_INC_PATH = include/SDL2
SDL2_LIB_PATH = lib

SDL_VER = 2.0.8
TTF_VER = 2.0.14
IMG_VER = 2.0.3
MIX_VER = 2.0.2_3

LFT_LIB_NAME = libft
SDL_LIB_NAME = sdl2
TTF_LIB_NAME = sdl2_ttf
IMG_LIB_NAME = sdl2_image
MIX_LIB_NAME = sdl2_mixer

LFT_PATH = $(PROJ_LIB_PATH)/$(LFT_LIB_NAME)
SDL_PATH = $(PROJ_LIB_PATH)/$(SDL_LIB_NAME)/$(SDL_VER)
TTF_PATH = $(PROJ_LIB_PATH)/$(TTF_LIB_NAME)/$(TTF_VER)
IMG_PATH = $(PROJ_LIB_PATH)/$(IMG_LIB_NAME)/$(IMG_VER)
MIX_PATH = $(PROJ_LIB_PATH)/$(MIX_LIB_NAME)/$(MIX_VER)

PRJ_INC = -I $(PROJ_INC_PATH)
LFT_INC = -I $(LFT_PATH)/
SDL_INC = -I $(SDL_PATH)/$(SDL2_INC_PATH)
TTF_INC = -I $(TTF_PATH)/$(SDL2_INC_PATH)
IMG_INC = -I $(IMG_PATH)/$(SDL2_INC_PATH)
MIX_INC = -I $(MIX_PATH)/$(SDL2_INC_PATH)

#end sdl2 section (with brew installed library)

LFT_LNK = -L $(LFT_PATH)
SDL_LNK = -L $(SDL_PATH)/$(SDL2_LIB_PATH)
TTF_LNK = -L $(TTF_PATH)/$(SDL2_LIB_PATH)
IMG_LNK = -L $(IMG_PATH)/$(SDL2_LIB_PATH)
MIX_LNK = -L $(MIX_PATH)/$(SDL2_LIB_PATH)

LFT_LIB = -l ft
SDL_LIB = -l SDL2
TTF_LIB = -l SDL2_ttf
IMG_LIB = -l SDL2_image
MIX_LIB = -l SDL2_mixer

ALL_INC = $(SDL_INC) $(TTF_INC) $(IMG_INC) $(MIX_INC) $(LFT_INC) $(PRJ_INC)
ALL_LNK = $(SDL_LNK) $(TTF_LNK) $(IMG_LNK) $(MIX_LNK) $(LFT_LNK)
ALL_LIB = $(SDL_LIB) $(TTF_LIB) $(IMG_LIB) $(MIX_LIB) $(LFT_LIB)
ALL_FW  = $(SDL_FW)  $(TTF_FW)  $(IMG_FW)  $(MIX_FW)

SRC_NAMES = color.c \
			draw.c \
			get_next_line.c \
			interface.c \
			keys.c \
			main.c \
			init.c \
			parser.c

SRC = $(addprefix $(PROJ_SRC_PATH)/, $(SRC_NAMES))

OBJ = $(addprefix ./$(PROJ_OBJ_PATH)/, $(SRC_NAMES:.c=.o))

all: $(NAME)

./$(PROJ_OBJ_PATH)/%.o: ./$(PROJ_SRC_PATH)/%.c
	$(CC) $(ALL_INC) -c $< -o $@

$(NAME): objdir liball $(OBJ)
	$(CC) $(ALL_INC) $(ALL_LNK) $(ALL_LIB) $(OBJ) -o $(NAME)

objdir:
	mkdir -p $(PROJ_OBJ_PATH)

clean: libclean
	rm -rf $(PROJ_OBJ_PATH)

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

norm:
	norminette $(LFT_PATH)/*.c
	norminette $(LFT_PATH)/*.h
	norminette $(PROJ_SRC_PATH)/*.c
	norminette $(PROJ_INC_PATH)/*.h

normf:
	@norminette $(NORMFLAGS) $(LFT_PATH)/*.c  | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) $(LFT_PATH)/*.h  | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) $(PROJ_SRC_PATH)/*.c  | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) $(PROJ_INC_PATH)/*.h  | grep -E '^(Error|Warning)'

.phony: all clean fclean re
