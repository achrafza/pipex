SRC=  ft_printad.c ft_printf.c ft_putchar_fp.c ft_putnbr_pf.c ft_putnbr_pfu.c ft_putnbrhexa1.c ft_putnbrhexa2.c ft_putstr_fp.c

CC= cc

CFLAGS= -Wall -Wextra -Werror

NAME= libftprintf.a 

OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@
clean:
	rm -f $(OBJ) 
fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean
