# ifndef SO_LONG_H
# define SO_LONG_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include "/home/abdalrhman/test/Libft/libft.h"
# include "file_error.h"
# include "map_error.h"

# define UP_KEY 65362
typedef struct s_game_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int        width;
    int        height;
    int        x;
    int        y;
    int        *map;
    int        player_x;
    int        player_y;
}                t_game_data;

char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(char *str);
char	*check_for_newline(char *str);
char	*get_next_line(int fd);

#endif