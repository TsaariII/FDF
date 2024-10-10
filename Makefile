NAME := fdf

SRC =	fdf.c\
		clip.c\
		clip2.c\
		draw.c\
		draw_utils.c\
		hooks.c\
		initialize.c\
		map_parse.c\
		colours.c\
		rotation.c\
		rotation2.c\
		utils.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c

FLAGS = -Wall -Werror -Wextra -g

OFLAGS = -ldl -lglfw -pthread -lm

LIBFT = $(LIBFT_DIR)/libft.a

LIBFT_DIR = ./libft

PRINTF = $(PRINTF_DIR)/libftprintf.a

PRINTF_DIR = ./ft_printf

MLX = ./MLX42

MLX_HEAD = -I $(MLX)/include

LIBMLX = $(MLX)/build/libmlx42.a

HEADS = -I. $(MLX_HEAD) -I$(LIBFT_DIR)

MAKEFLAGS += --no-print-directory

all: $(PRINTF) $(LIBFT) $(LIBMLX) $(NAME)

$(LIBMLX):
		@if [ ! -d "$(MLX)" ]; then \
			echo "\n\033[0;33mCloning MLX...\033[0m\n"; \
			git clone https://github.com/codam-coding-college/MLX42.git $(MLX) > /dev/null 2>&1; \
		fi
		@if [ ! -d "$(MLX)/build" ]; then \
			cmake $(MLX) -B $(MLX)/build > /dev/null; \
		fi
		@make -C $(MLX)/build -j4 > /dev/null
		@echo "\n\033[0;32mMLX ready\033[0m\n"

$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
		@$(MAKE) -C $(PRINTF_DIR)

OBJS = $(SRC:.c=.o)

%.o: %.c
		@cc $(FLAGS) -c $< -o $@ $(HEADS)

$(NAME): $(OBJS)
		@echo "\n\033[0;32mLibft ready\033[0m\n"
		@cc $(OBJS) $(PRINTF) $(LIBMLX) $(LIBFT) $(OFLAGS) -o $(NAME) > /dev/null
		@echo "\n\033[0;32mLet's make maps!\033[0m\n"

clean:
		@rm -f $(OBJS)
		@rm -rf $(MLX)/build
		@$(MAKE) -C $(LIBFT_DIR) clean
		@$(MAKE) -C $(PRINTF_DIR) clean

fclean:
		@rm -f $(NAME)
		@rm -f $(OBJS)
		@$(MAKE) -C $(PRINTF_DIR) fclean
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@rm -rf $(MLX)
		@rm -f fdf.a
		@echo "\n\033[0;31mAll is gone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libmlx libft
