NAME		=	philo

SRC			=	$(wildcard srcs/*.c)

OBJ_DIR		=	obj

OBJ			=	$(patsubst srcs/%.c, $(OBJ_DIR)/%.o, $(SRC))

FLAGS		=	-Wall -Wextra -Werror -g -pthread

INC			=	includes

GREEN		= \033[38;5;47m
YELLOW		= \033[38;5;226m
RED			= \033[38;5;196m
RESET 		= \033[0m

$(OBJ_DIR)/%.o: srcs/%.c | $(OBJ_DIR)
	@cc $(FLAGS) -c $< -o $@
	@echo "[$(GREEN)compiling$(RESET)]: $<"

all: $(NAME)
	@echo "$(GREEN)$(NAME) executable created$(RESET)"

$(NAME): $(OBJ) $(LIBFT)
	@cc $(FLAGS) -I $(INC) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	@mkdir obj/

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Removing objects files$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)removing $(NAME) executable$(RESET)"

re: fclean all

.PHONY: all clean fclean re