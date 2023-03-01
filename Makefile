CC		=	gcc

AR		=	ar

CFLAGS	=	-I. -Wall -Wextra -Werror

NAME	=	get_next_line.a

SRC		= 	get_next_line.c \
			get_next_line_utils.c

BONUS	= 	get_next_line_bonus.c \
			get_next_line_utils_bonus.c

OBJ		=	$(SRC:.c=.o)

OBJ_B	= 	$(SRC_B:.c=.o)

DEPS	=	get_next_line.h get_next_line_bonus.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rcs $@ $^

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJ_B)
	ar rcs $(NAME) $^

.PHONY: all clean fclean re