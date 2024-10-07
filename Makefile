NAME = objdump

CC = clang
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
SRC_DIR = src
OBJ_DIR = obj
HSRCS = include

SRC = $(shell find src -name '*.c')
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -I $(HSRCS) -o $@ -c $<

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@if [ -f $(NAME) ]; then \
		echo "$(RED)Cleaning executable $(NAME)...$(NC)"; \
		rm -f $(NAME); \
		fi

re: fclean all

.PHONY: all clean fclean re

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m
