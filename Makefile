NAME := fdf

SRC =	fdf.c\
		draw.c\
		draw_utils.c\
		initialize.c\
		map_parse.c\
		colours.c\
		utils.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c

FLAGS = -Wall -Werror -Wextra

OFLAGS = -ldl -lglfw -pthread -lm

LIBFT = $(LIBFT_DIR)/libft.a

LIBFT_DIR = ./libft

PRINTF = $(PRINTF_DIR)/ft_printf.a

PRINTF_DIR = ./ft_printf

MLX = ./MLX42

MLX_HEAD = -I $(MLX)/include

LIBMLX = $(MLX)/build/libmlx42.a

HEADS = -I. $(MLX_HEAD) -I$(LIBFT_DIR)

all: $(PRINTF) $(LIBFT) $(LIBMLX) $(NAME)

$(LIBMLX):
		@if [ ! -d "$(MLX)" ]; then \
			git clone https://github.com/codam-coding-college/MLX42.git $(MLX); \
		fi
		@if [ ! -d "$(MLX)/build" ]; then \
			cmake $(MLX) -B $(MLX)/build; \
		fi
		@make -C $(MLX)/build -j4

$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
		@$(MAKE) -C $(PRINTF_DIR)

OBJS = $(SRC:.c=.o)


%.o: %.c
		cc $(FLAGS) -c $< -o $@ $(HEADS)

$(NAME): $(OBJS)
		@cc $(OBJS) $(LIBMLX) $(LIBFT) $(OFLAGS) -o $(NAME)
		@echo "\n\033[0;32mLet's examine this map!\033[0m\n]"

clean:
		@rm -f $(OBJS)
		@rm -rf $(MLX)/build
		@$(MAKE) -C $(LIBFT_DIR) clean
		@$(MAKE) -C $(PRINTF_DIR) clean

fclean:
		rm -f $(NAME)
		@$(MAKE) -C $(PRINTF_DIR) fclean
		@$(MAKE) -C $(LIBFT_DIR) fclean
		rm -rf $(MLX)

re: fclean all

.PHONY: all clean fclean re libmlx libft
