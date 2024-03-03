# declare makefile variables
NAME = minishell
BONUS = minishell_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# libft path and flags
LIBFT = libft.a
LIB_DIR = ./libft
LIB_FLAGS = -L $(LIB_DIR) -lft -lreadline
INC = -I ./includes

#------------------------------------------------------------------------

# minishell targets
# init
INIT = main.c \
	init_utils.c \
	init_minishell.c \
	init_env.c
INIT_SRCS = $(addprefix srcs/init/, $(INIT))

# lexer
LEXER = lexer.c \
	lexer_utils.c \
	lexer_helper.c \
	lexer_list.c \
	free_tokens.c \
	lexer_symbol.c \
	lexer_string.c \
	lexer_tokens.c \
	lexer_error.c
LEXER_SRCS = $(addprefix srcs/lexer/, $(LEXER))

# parser
PARSER = parser.c \
	parser_utils.c \
	parser_helper.c \
	parser_nodes.c \
	parser_cmd.c \
	parser_io.c \
	parser_redir.c \
	free_ast.c
PARSER_SRCS = $(addprefix srcs/parser/, $(PARSER))

# expander
EXP = expander.c \
	expand_var.c \
	wildcard.c \
	pattern.c \
	utils/expand_var_utils.c \
	utils/ft_split_argv.c \
	utils/ft_split_whitespace.c \
	utils/readdir_utils.c \
	utils/remove_quotes.c
EXP_SRCS = $(addprefix srcs/expander/, $(EXP))

# execution
EXEC = exec.c \
	exec_utils.c \
	exec_heredoc.c \
	exec_cmd.c \
	exec_path.c \
	exec_redir.c \
	exec_open.c \
	exec_handler.c \
	exec_pipe.c
EXEC_SRCS = $(addprefix srcs/execution/, $(EXEC))

# builtins
BUILTIN = check_builtin.c \
	exec_builtin.c \
	ft_cd.c \
	ft_echo.c \
	ft_env.c \
	ft_exit.c \
	ft_export.c \
	ft_pwd.c \
	ft_unset.c
BUILTIN_SRCS = $(addprefix srcs/builtins/, $(BUILTIN))

# environment
ENV = envp_dup.c \
	sort_envp.c \
	update_envp.c \
	search_envp.c
ENV_SRCS = $(addprefix srcs/env/, $(ENV))

# error utils
ERR = set_exit_status.c \
	error_expander.c \
	error_builtin.c \
	error_exec.c \
	print_error.c \
	free_data.c
ERR_SRCS = $(addprefix srcs/error/, $(ERR))

# signals
SIG = signals.c \
	signals_utils.c
SIG_SRCS = $(addprefix srcs/signals/, $(SIG))

# all srcs
SRCS = $(INIT_SRCS) $(BUILTIN_SRCS) $(EXP_SRCS) $(ERR_SRCS) \
	$(LEXER_SRCS) $(PARSER_SRCS) $(EXEC_SRCS) $(ENV_SRCS) $(SIG_SRCS)
OBJS = $(SRCS:.c=.o)

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

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_FLAGS) $(INC)
	@echo "\n$(B_GREEN)$(NAME) compiled.$(END)"

bonus: $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(BONUS) $(LIB_FLAGS) $(INC)
	@echo "\n$(B_GREEN)$(BONUS) compiled.$(END)"

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\t$(BROWN)$< compiled.$(END)"

$(LIBFT):
	@echo "\n$(B_BROWN)[ COMPILING: $(LIBFT) ]$(END)"
	@make -s -C $(LIB_DIR)
	@echo "\n$(B_BROWN)[ COMPILING: $(NAME) ]$(END)"

# remove temporary generated files
clean:
	@$(RM) $(OBJS)
	@make clean -s -C $(LIB_DIR)

# remove library and executable file
fclean: clean
	@$(RM) $(NAME) $(BONUS)
	@cd $(LIB_DIR) && $(RM) $(LIBFT)
	@echo "$(B_GREEN)Removed $(NAME) and $(LIBFT).$(END)"

re: fclean all

#------------------------------------------------------------------------

# declare phony
.PHONY: all bonus clean fclean re
