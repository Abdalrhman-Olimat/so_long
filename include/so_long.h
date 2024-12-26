#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define TILE_SIZE 65
# define NUM_COLLECTIBLE_FRAMES 6 // Number of frames for the collectible animation
# define FRAME_DELAY 33 // Number of game loop iterations per frame change
# define ENEMY_MOVE_DELAY 100 // Number of game loop iterations per enemy move
# define MAX_ENEMIES 10000 // Maximum number of enemies

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "/home/abdalrhman/so_long/Libft/libft.h"

typedef struct s_map
{
    char    **map;
    int     width;
    int     height;
    int     player_x;
    int     player_y;
    int     collectibles;
}   t_map;

typedef struct s_enemy
{
    int x;
    int y;
}   t_enemy;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_map   map;
    t_enemy enemies[MAX_ENEMIES];
    int     num_enemies;
    void    *img_wall;
    void    *img_floor;
    //void    *img_gold;////////////////////////////////
    void    *img_player;
    void    *img_exit;
    void    *img_collectibles[NUM_COLLECTIBLE_FRAMES]; // Array of collectible frames
    void    *img_enemy; // Enemy image
    int     current_frame; // Current frame index for animation
    int     frame_counter; // Frame counter for controlling animation speed
    int     move_count; // Move counter
}   t_game;

// Function prototypes
void init_game(t_game *game);
void init_images(t_game *game);
void render_map(t_game *game);
void cleanup_game(t_game *game);
int  handle_keypress(int keysym, t_game *game);
int  handle_close(t_game *game);
int  game_loop(t_game *game);
void move_player(t_game *game, int dx, int dy);
void move_enemies(t_game *game);
int  load_map2(char *filename, t_game *game);
int  check_path(char **map, int height, int width, int px, int py, int total);
void free_map(char **map, int height);

# include "file_error.h"
# include "map_error.h"

char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(char *str);
char	*check_for_newline(char *str);
char	*get_next_line(int fd);

#endif