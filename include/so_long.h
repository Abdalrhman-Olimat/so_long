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
# include "/home/abdalrhman/so_long/Libft/libft.h"

#define TILE_SIZE 36
typedef struct s_map
{
    char **map;
    int width;
    int height;
    int player_x;
    int player_y;
    int collectibles;
} t_map;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_map   map;
    void    *img_wall;
    void    *img_floor;
    void    *img_player;
    void    *img_collectible;
    void    *img_exit;
} t_game;

// Function prototypes
void    init_game(t_game *game);
void    init_images(t_game *game);
void    render_map(t_game *game);
void    cleanup_game(t_game *game);
int     handle_keypress(int keysym, t_game *game);
int     handle_close(t_game *game);
int     game_loop(t_game *game);
void    move_player(t_game *game, int dx, int dy);

void    free_map(char **map, int height);
int     load_map(char *filename, t_map *data);
int     check_path(char **map, int height, int width, int player_x, int player_y, int total_collectibles);

# include "file_error.h"
# include "map_error.h"


char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(char *str);
char	*check_for_newline(char *str);
char	*get_next_line(int fd);

#endif