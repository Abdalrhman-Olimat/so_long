NAME = test
CC = cc
SRC = test.c get_next_line.c get_next_line_utils.c map_error.c map_error2.c file_error.c
LIBFT = Libft/libft.a
INCS	= -I ./include/
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	make all -C Libft 
	$(CC) $(OBJ) $(INCS) -I./Libft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libft  

c:
	rm -rf $(OBJ) $(NAME)
	make fclean -C Libft

re: c all
