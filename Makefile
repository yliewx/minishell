# declare makefile variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# libft path and flags
LIBFT = libft.a
LIB_DIR = ./libft
LIB_FLAGS = -L $(LIB_DIR) -lft -I ./libft/includes

# minishell targets
TARGET = 
SRCS = $(addprefix srcs/, $(TARGET))
INC = -I ./includes

# colours
GREEN = \033[0;32m
B_GREEN = \033[1;32m
BROWN = \033[0;33m
B_BROWN = \033[1;33m
END = \033[0m

# RULES
# all = create library from sub-make

all: $(LIBFT) $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	@echo "\n$(B_BROWN)[ COMPILING: $(NAME) ]$(END)"
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIB_FLAGS) $(INC)
	@echo "$(B_GREEN)$(NAME) compiled.$(END)"

$(LIBFT):
	@echo "\n$(B_BROWN)[ COMPILING: $(LIBFT) ]$(END)"
	@make -s -C $(LIB_DIR)

# remove temporary generated files
clean:
	@make clean -s -C $(LIB_DIR)

# remove library and executable file
fclean: clean
	@$(RM) $(NAME)
	@cd $(LIB_DIR) && $(RM) $(LIBFT)
	@echo "$(B_GREEN)Removed $(NAME) and $(LIBFT).$(END)"

re: fclean all

# declare phony
.PHONY: all clean fclean re
