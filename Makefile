NAME = so_long
CC = cc
CFLAG = -Wall -Werror -Wextra
SRC_PATH = src/
OBJ_PATH = obj/
SRC = main.c get_next_line.c get_next_line_utils.c map_error.c map_error2.c file_error.c load_map.c flood_file.c enemie.c\
	init.c movement.c render_loop.c cleanup.c load_map2help.c 
LIBFT = Libft/libft.a
INCS	= -I ./include/
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS) $(LIBFT)
	make all -C Libft 
	make -C mlx_linux
	$(CC) $(CFLAG) $(OBJS) -I./Libft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libft  

clean:
	rm -rf $(OBJ_PATH) $(NAME)
	make clean -C Libft
fclean: clean
	rm -rf $(NAME)
	make fclean -C Libft

re: fclean all
