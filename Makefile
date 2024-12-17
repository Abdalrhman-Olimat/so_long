NAME = test
CC = cc
SRC = test.c get_next_line.c get_next_line_utils.c
LIBFT = Libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	make all -C Libft  # Build libft.a before linking
	$(CC) $(OBJ) -I./Libft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libft  

c:
	rm -rf $(OBJ) $(NAME)
	make fclean -C Libft

re: c all
	# rm -rf $(OBJ) $(NAME)
	# make fclean -C Libft
