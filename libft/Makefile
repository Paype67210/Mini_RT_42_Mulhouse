NAME = libft.a
HEADERS = libft.h def_list.h
DIR_OBJS = .objs/
CC = @gcc -DM
FLAGS = -Wall -Wextra -Werror -g3
AR = ar -rcs
RM = rm -rf

# Creation of sources
SRCES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_isalpha.c ft_isalnum.c \
		ft_isdigit.c ft_isascii.c ft_isprint.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		ft_tolower.c ft_toupper.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_spsplit.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstlast.c get_next_line.c \
		ft_printf.c ft_printf_utils.c ft_print_ptr.c ft_print_unsigned.c ft_print_hex.c \
		ft_free_array.c ft_free_2d.c ft_wcount.c ft_char_end.c ft_char_start.c \
		ft_msg.c ft_int_strchr.c ft_split_args_cmd.c ft_lstclear_safe.c \
		ft_lstremove.c ft_lstretrieve.c ft_strnchr.c ft_strwchr.c ft_strcmp.c \
		ft_strnlcpy.c ft_lstfirst.c ft_strbtwcpy.c ft_lstreplace.c \
		ft_lstaddafter.c ft_lstaddbefore.c ft_malloc.c ft_strncpy.c ft_strstr.c \
		ft_error_varlog.c ft_fprintf.c ft_putnbr_base_fd.c ft_putptr_fd.c \
		ft_lstcopy.c ft_strcpy.c ft_strwchr.c ft_isspace.c ft_strtof.c \
		ft_strtod.c ft_strtof.c ft_strtof_utils.c \

# Generate a list of object files
LIST_OBJS = $(SRCES:.c=.o)
OBJS = $(addprefix $(DIR_OBJS), $(LIST_OBJS))

all: $(DIR_OBJS) $(OBJS) $(NAME)

# Use a pattern rule to compile source files to object files
$(DIR_OBJS)%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ -I .

# Create the library
$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS) -lm
	@ranlib $(NAME)
	@echo "Libft compiled!"

# Don't Relink
$(OBJS): $(HEADERS)

clean:
	@$(RM) $(DIR_OBJS)
	@echo "libft objects files cleaned!"

fclean:	clean
	@$(RM) $(NAME)
	@echo "libft executable files cleaned!"

re: fclean all
	@echo "Cleaned and rebuilt everything for libft!"

norm:
	@norminette $(SRCES) $(HEADERS) | grep -v Norme -B1 || true

$(DIR_OBJS):
	@mkdir -p $(DIR_OBJS)

.PHONY : all norm clean fclean re
