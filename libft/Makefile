# declare makefile variables
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ar -rcs
RM = rm -f

# source directories
DIR = srcs
INC = includes

# file targets
TARGET = ft_atoi.c ft_atoi_long.c ft_bzero.c ft_calloc.c ft_isalnum.c \
	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	ft_toupper.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
	ft_lstsize.c ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c \
	ft_puthex.c get_next_line.c

# source files & object files
SRCS = $(addprefix $(DIR)/, $(TARGET))
OBJS = $(SRCS:.c=.o)

# colours
GREEN = \033[0;32m
B_GREEN = \033[1;32m
BROWN = \033[0;33m
B_BROWN = \033[1;33m
END = \033[0m

# RULES
# all = create libft.a
all: $(NAME)

# create library with source files
$(NAME): $(OBJS)
	@$(LIB) $@ $^
	@echo "$(B_GREEN)$@ created.$(END)"

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@echo "\t$(BROWN)$< compiled.$(END)"

# compile executable for testing
test: $(SRCS)
	$(CC) $(CFLAGS) -lbsd $^ -I $(INC)

# remove temporary generated files
clean:
	@$(RM) $(OBJS)
	@echo "$(B_GREEN)Removed all obj files.$(END)"

# clean + remove library
fclean: clean
	@$(RM) $(NAME)
	@echo "$(B_GREEN)Removed $(NAME).$(END)"

# fclean followed by make all
re: fclean all

# declare phony
.PHONY: all clean fclean re test
