NAME := fdf

SRC =	fdf.c\
		$(addprefix fdf/, colours.c draw_utils.c draw.c initialize.c map_parse.c)

FLAGS = -Wall -Werror -Wextra

OFLAGS = -ldl -lglfw -pthread -lm

LIBFT = $(LIBFT_DIR)/libft.a

LIBFT_DIR = ./libft

MLX = ./MLX42

MLX_HEAD = -I $(MLX)/include

LIBMLX = $(MLX)/build/libmlx42.a

HEADS = -I. $(MLX_HEAD) -I$(LIBFT_DIR)

all: $(LIBFT) $(LIBMLX) $(NAME)

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

OBJS = $(SRC: .c=.o)


%.o: %.c
		cc $(FLAGS) -c $< -o $@ $(HEADS)

$(NAME): $(OBJS)
		@cc $(OBJS) $(LIBMLX) $(LIBFT) $(OFLAGS) -o $(NAME)
		@echo "\n\033[0;32mLet's examine this map!\033[0m\n]"

clean:
		@rm -rf $(OBJS)
		@rm -rf $(MLX)/build
		@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
		rm -rf $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		rm -rf $(MLX)

re: fclean all

.PHONY: all clean fclean re libmlx libft
