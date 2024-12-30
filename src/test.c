/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:44:56 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/30 11:54:05 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/home/abdalrhman/so_long/include/so_long.h"

// Initialize the game and create the window
void init_game(t_game *game)
{
    int window_width;
    int window_height;
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        write(2, "Error initializing MLX\n", 23);
        exit(1);
    }
    game->move_count = 0;
    game->current_frame = 0;
    game->frame_counter = 0;
    window_width = game->map.width * TILE_SIZE;
    window_height = game->map.height * TILE_SIZE;
    game->win = mlx_new_window(game->mlx, window_width, window_height, "so_long");
    if (!game->win)
    {
        write(2, "Error creating window\n", 22);
        exit(1);
    }
}

void init_images_helper(t_game *game, int img_width, int img_height, char *collectible_paths[])
{
    int i;

    i = 0;
    while (i < NUM_COLLECTIBLE_FRAMES)
    {
    game->img_collectibles[i] = mlx_xpm_file_to_image(game->mlx, collectible_paths[i], &img_width, &img_height);
    if (!game->img_collectibles[i])
    {
    write(2, "Error loading collectible images\n", 33);
    exit(1);
    }
    i++;
    }
}

void init_images(t_game *game)
{
    int img_width;
    int img_height;
    char *collectible_paths[NUM_COLLECTIBLE_FRAMES] =
    {
        "image/collectible/gold2.xpm",
        "image/collectible/gold3.xpm",
        "image/collectible/gold4.xpm",
        "image/collectible/gold5.xpm",
        "image/collectible/gold6.xpm",
        "image/collectible/gold7.xpm"
    };
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "image/wall.xpm", &img_width, &img_height);
    game->img_floor = mlx_xpm_file_to_image(game->mlx, "image/floor.xpm", &img_width, &img_height);
    game->img_player = mlx_xpm_file_to_image(game->mlx, "image/player.xpm", &img_width, &img_height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "image/exit.xpm", &img_width, &img_height);
    game->img_enemy = mlx_xpm_file_to_image(game->mlx, "image/enemy.xpm", &img_width, &img_height);
    init_images_helper(game, img_width, img_height, collectible_paths);
    if (!game->img_wall || !game->img_floor || !game->img_player || !game->img_exit || !game->img_enemy)
    {
        write(2, "Error loading images\n", 21);
        exit(1);
    }
}

// Render the map and objects
void draw_map(t_game *game, int x, int y, int screen_x, int screen_y)
{
    mlx_put_image_to_window(game->mlx, game->win, game->img_floor, screen_x, screen_y);
    if (game->map.map[y][x] == '1')
        mlx_put_image_to_window(game->mlx, game->win, game->img_wall, screen_x, screen_y);
    if (game->map.map[y][x] == 'C')
        mlx_put_image_to_window(game->mlx, game->win, game->img_collectibles[game->current_frame], screen_x, screen_y);
    if (game->map.map[y][x] == 'E')
        mlx_put_image_to_window(game->mlx, game->win, game->img_exit, screen_x, screen_y);
    if (game->map.map[y][x] == 'P')
        mlx_put_image_to_window(game->mlx, game->win, game->img_player, screen_x, screen_y);
}

void draw_enemies(t_game *game)
{
	int i = 0;
    while (i < game->num_enemies)
    {
		int screen_x;
		int screen_y;
		screen_x = game->enemies[i].x * TILE_SIZE;
		screen_y = game->enemies[i].y * TILE_SIZE;
		mlx_put_image_to_window(game->mlx, game->win, game->img_enemy, screen_x, screen_y);
		i++;
    }
}
void render_map(t_game *game)
{
    int x;
    int y;
    int i;
    char    *moves_str;
    
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            int screen_x;
            int screen_y;
            
            screen_x = x * TILE_SIZE;
            screen_y = y * TILE_SIZE;
            draw_map(game, x, y, screen_x, screen_y);
            x++;
        }
        y++;
    }
    i = 0;
        draw_enemies(game);
    moves_str = ft_itoa(game->move_count);
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFF0000, moves_str);
    free(moves_str);
}
// Handle key presses
int handle_keypress(int keysym, t_game *game)
{
	int i;
	
	i = 0;
    if (keysym == XK_Escape)
    {
        cleanup_game(game);
        exit(0);
    }
    if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
        move_player(game, 0, -1, i);
    else if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
        move_player(game, 0, 1, i);
    else if (keysym == XK_a || keysym == XK_A || keysym == XK_Left)
        move_player(game, -1, 0, i);
    else if (keysym == XK_d || keysym == XK_D || keysym == XK_Right)
        move_player(game, 1, 0, i);
    return (0);
}
void print_on_terminal(t_game *game)
{
	char *move_str;
	
	move_str = ft_itoa(game->move_count);
	write(1, "Moves: ", 7);
	write(1, move_str, ft_strlen(move_str));
	write(1, "\n", 1);
	free(move_str);
}

// Move player function
int move_player_help(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == '1')
        return 1;
    if (game->map.map[new_y][new_x] == 'E' && game->map.collectibles > 0)
    {
        write(1, "Collect all collectibles before exiting!\n", 41);
        return 1;
    }
    if (game->map.map[new_y][new_x] == 'E' && game->map.collectibles == 0)
    {
        write(1, "You win!\n", 9);
        cleanup_game(game);
        exit(0);
    }
    if (game->map.map[new_y][new_x] == 'C')
    {
        game->map.collectibles--;
        game->map.map[new_y][new_x] = '0';
    }
	return 0;
}
void move_player(t_game *game, int dx, int dy, int i)
{
    int new_x;
    int new_y;

    new_x = game->map.player_x + dx;
    new_y = game->map.player_y + dy;
    if (move_player_help(game, new_x, new_y))
        return;
    while (i < game->num_enemies)
    {
        if (new_x == game->enemies[i].x && new_y == game->enemies[i].y)
        {
            write(1, "You were caught by an enemy!\n", 29);
            cleanup_game(game);
            exit(0);
        }
        i++;
    }
    game->map.map[game->map.player_y][game->map.player_x] = '0';
    game->map.map[new_y][new_x] = 'P';
    game->map.player_x = new_x;
    game->map.player_y = new_y;
    game->move_count++;
    print_on_terminal(game);
    render_map(game);
}

int	is_valid_enemy_move(t_game *game, int new_x, int new_y, int enemy_index)
{
    if (new_x < 0 || new_x >= game->map.width ||
        new_y < 0 || new_y >= game->map.height)
        return 0;
    if (game->map.map[new_y][new_x] == '1' ||
        game->map.map[new_y][new_x] == 'C' ||
        game->map.map[new_y][new_x] == 'E')
        return 0;
    if (new_x == game->map.player_x && new_y == game->map.player_y)
    {
        write(1, "You were caught by an enemy!\n", 29);
        cleanup_game(game);
        exit(0);
    }
    int j;
	
	j = 0;
    while (j < game->num_enemies)
    {
        if (j != enemy_index && game->enemies[j].x == new_x && game->enemies[j].y == new_y)
            return 0;
        j++;
    }
    return 1;
}

void calculate_enemy_move(int *dx, int *dy)
{
    int direction;
	
	direction = rand() % 4;
    *dx = 0;
    *dy = 0;
    if (direction == 0)
        *dx = 1;
    else if (direction == 1)
        *dx = -1;
    else if (direction == 2)
        *dy = 1;
    else if (direction == 3)
        *dy = -1;
}

void move_enemies(t_game *game)
{
    int i = 0;
    while (i < game->num_enemies)
    {
        int dx, dy;
        calculate_enemy_move(&dx, &dy);
        int new_x;
        int new_y;
		
		new_x = game->enemies[i].x + dx;
		new_y = game->enemies[i].y + dy;
        if (!is_valid_enemy_move(game, new_x, new_y, i))
        {
            i++;
            continue;
        }
        game->map.map[game->enemies[i].y][game->enemies[i].x] = '0';
        game->map.map[new_y][new_x] = 'D';
        game->enemies[i].x = new_x;
        game->enemies[i].y = new_y;

        i++;
    }
}




// Clean up resources
void cleanup_game(t_game *game)
{
    if (game->img_wall)
    {
        mlx_destroy_image(game->mlx, game->img_wall);
        game->img_wall = NULL;
    }
    if (game->img_floor)
    {
        mlx_destroy_image(game->mlx, game->img_floor);
        game->img_floor = NULL;
    }
    if (game->img_player)
    {
        mlx_destroy_image(game->mlx, game->img_player);
        game->img_player = NULL;
    }
    if (game->img_exit)
    {
        mlx_destroy_image(game->mlx, game->img_exit);
        game->img_exit = NULL;
    }
    for (int i = 0; i < NUM_COLLECTIBLE_FRAMES; i++)
    {
        if (game->img_collectibles[i])
        {
            mlx_destroy_image(game->mlx, game->img_collectibles[i]);
            game->img_collectibles[i] = NULL;
        }
    }
    if (game->img_enemy)
    {
        mlx_destroy_image(game->mlx, game->img_enemy);
        game->img_enemy = NULL;
    }
    if (game->win)
    {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
    }
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
    }
    if (game->mlx)
    {
        free(game->mlx);
        game->mlx = NULL;
    }
    if (game->map.map)
    {
        free_map(game->map.map, game->map.height);
        game->map.map = NULL;
    }
}

int handle_close(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}

int game_loop(t_game *game)
{
    game->frame_counter++;
    if (game->frame_counter >= FRAME_DELAY)
    {
        game->current_frame = (game->current_frame + 1) % NUM_COLLECTIBLE_FRAMES;
        game->frame_counter = 0; // Reset the frame counter
    }
    static int enemy_move_counter = 0;
    enemy_move_counter++;
    if (enemy_move_counter >= ENEMY_MOVE_DELAY)
    {
        move_enemies(game);
        enemy_move_counter = 0;
    }
    render_map(game);

    return (0);
}

int load_map2(char *filename, t_game *game)
{
    int	fd;
	
	fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);

    game->map.height = 0;
    game->map.width = 0;
    game->map.map = NULL;

    while (1)
    {
        char *line = get_next_line(fd);
        if (!line)
            break;

        // Remove trailing newline
        int len = ft_strlen2(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            len--;
        }
        // Track max width
        if (len > game->map.width)
            game->map.width = len;

        // Append new line to the map array
        char **tmp = malloc(sizeof(char *) * (game->map.height + 2));
        for (int i = 0; i < game->map.height; i++)
            tmp[i] = game->map.map[i];
        tmp[game->map.height] = line;
        tmp[game->map.height + 1] = NULL;

        free(game->map.map);
        game->map.map = tmp;
        game->map.height++;
    }
    close(fd);

    if (game->map.height == 0)
        return (0);

    // Initialize counters
    game->map.collectibles = 0;
    game->map.player_x = -1;
    game->map.player_y = -1;
    game->num_enemies = 0;

    // Scan map for objects
    for (int y = 0; y < game->map.height; y++)
    {
        for (int x = 0; x < game->map.width; x++)
        {
            char c = game->map.map[y][x];
            if (c == 'P')
            {
                game->map.player_x = x;
                game->map.player_y = y;
            }
            else if (c == 'C')
                game->map.collectibles++;
            else if (c == 'D' && game->num_enemies < MAX_ENEMIES)
            {
                game->enemies[game->num_enemies].x = x;
                game->enemies[game->num_enemies].y = y;
                game->num_enemies++;
            }
        }
    }
    return (1);
}

void error_handel(char *av, t_map *data)
{
    int i;
    
    cheack_name(av);
    cheack_empty(av);
    map_rectangular(av);
    map_wall_main(av);
    count_e_p_c(av);
    if (!load_map(av, data))
    {
        write(2, "Error loading map\n", 18);
        exit (1);
    }
    i = check_path(data->map, data->height, data->width,
                   data->player_x, data->player_y, data->collectibles);
    free_map(data->map, data->height);
    if (i == 0)
        exit (1);
}

int main(int ac, char **av)
{
    t_game  game;
    t_map   data;

    if (ac != 2)
    {
        write(2, "Usage: ./so_long <map_file>\n", 28);
        return (1);
    }
    error_handel(av[1], &data);
    ft_memset(&game, 0, sizeof(t_game));
    if (!load_map2(av[1], &game))
    {
        write(2, "Error loading map\n", 18);
        return (1);
    }
    init_game(&game);
    init_images(&game);
    render_map(&game);
    mlx_hook(game.win, ClientMessage, StructureNotifyMask, handle_close, &game);
    mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    cleanup_game(&game);
    return (0);
}
