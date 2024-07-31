NAME := fdf

FLAGS = -Wall -Werror -Wextra

OFLAGS = -ldl -lglfw -pthread -lm

LIBFT = $(LIBFT_DIR)/libft.a

LIBFT_DIR = ./libft

MLX = ./MLX42

MLX_HEAD = -I $(MLX_DIR)/include

LIBMLX = $(MLX)/build/libmlx42.a

HEADS = -I. $(MLX_HEAD) -I$(LIBFT_DIR)

$(LIBMLX):
		@if [! -d "$(MLX_DIR)"]; then \
			git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
		fi
		@if [! -d "$(MLX_DIR)/build"]; then \
			cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
		fi
		@make -C $(MLX_DIR)/build -j4



OBJS = $(SRC: .c=.o)

all: $(LIBFT) $(LIBMLX) $(NAME)

%.o: %.c
		cc $(FLAGS) -c $< -o $@ $(HEADS)

$(NAME): $(OBJS)
		@cc $(OBJS) $(LIBMLX) $(LIBFT) $(OFLAGS) -o $(NAME)

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
