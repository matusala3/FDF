NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/draw.c \
       $(SRC_DIR)/parse.c \
       $(SRC_DIR)/assign.c \
       $(SRC_DIR)/memory.c \
       $(SRC_DIR)/helper.c \
       $(SRC_DIR)/color.c \
       $(SRC_DIR)/projection.c \
       $(SRC_DIR)/rendering.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@make -s -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW) compiling: $<$(RESET)"

$(LIBFT):
	@make -s -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1
	@echo "$(GREEN)✅ Libft compiled."

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1 || true
	@echo "🧹 Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_DIR) --no-print-directory > /dev/null 2>&1 || true
	@echo "🧹 All files cleaned."

re: fclean all

.PHONY: all clean fclean re