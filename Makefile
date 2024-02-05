# declare makefile variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# libft path and flags
LIBFT = libft.a
LIB_DIR = ./libft
LIB_FLAGS = -L $(LIB_DIR) -lft
INC = -I ./includes -lreadline

#------------------------------------------------------------------------

# minishell targets
# init
INIT = main.c init_utils.c init_minishell.c init_env.c
INIT_SRCS = $(addprefix srcs/init/, $(INIT))

# lexer
LEXER = lexer.c lexer_utils.c lexer_helper.c lexer_list.c free_tokens.c
LEXER_SRCS = $(addprefix srcs/lexer/, $(LEXER))

# parser
PARSER = parser.c parser_utils.c parser_helper.c parser_nodes.c free_ast.c
PARSER_SRCS = $(addprefix srcs/parser/, $(PARSER))

# expander
EXP = expander.c wildcard.c pattern.c expander_utils.c dir_list_utils.c \
	ft_split_argv.c
EXP_SRCS = $(addprefix srcs/expander/, $(EXP))

# execution
EXEC = exec.c exec_utils.c exec_heredoc.c exec_cmd.c exec_path.c \
	exec_redir.c
EXEC_SRCS = $(addprefix srcs/execution/, $(EXEC))

# builtins
BUILTIN = exec_builtin.c ft_cd.c ft_echo.c ft_env.c ft_exit.c \
	ft_export.c ft_pwd.c ft_unset.c utils/check_builtin.c \
	utils/builtin_errors.c utils/remove_quotes.c
BUILTIN_SRCS = $(addprefix srcs/builtins/, $(BUILTIN))

# environment
ENV = envp_dup.c sort_envp.c update_envp.c search_envp.c
ENV_SRCS = $(addprefix srcs/env/, $(ENV))

# error utils
ERR = set_exit_status.c signals.c free_data.c
ERR_SRCS = $(addprefix srcs/error/, $(ERR))

# all srcs
SRCS = $(INIT_SRCS) $(BUILTIN_SRCS) $(EXP_SRCS) $(ERR_SRCS) \
	$(LEXER_SRCS) $(PARSER_SRCS) $(EXEC_SRCS) $(ENV_SRCS)

#------------------------------------------------------------------------

# colours
GREEN = \033[0;32m
B_GREEN = \033[1;32m
BROWN = \033[0;33m
B_BROWN = \033[1;33m
END = \033[0m

#------------------------------------------------------------------------

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

#------------------------------------------------------------------------

# declare phony
.PHONY: all clean fclean re
