/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:44:56 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/18 15:08:59 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/home/abdalrhman/so_long/include/so_long.h"

/*void error_handel(char *av, t_map data)
{
    int i;
    
	cheack_name(av);
	cheack_empty(av);
	map_rectangular(av);
	map_wall_main(av);
	count_e_p_c(av);
	if (!load_map(av, &data))
    {
        write(2, "Error loading map\n", 18);
        exit (1);
    }
    i = check_path(data.map, data.height, data.width, data.player_x, data.player_y, data.collectibles);
    free_map(data.map, data.height);
    if (i == 0)
        exit (1);
}


int main(int ac, char **av)
{
    t_map data;
    if (ac != 2)
    {
        write(2, "Error1\n", 7);
        return (0);
    }
    error_handel(av[1], data);
    return (0);
}*/
#include "/home/abdalrhman/so_long/include/so_long.h"



// Initialize the game and create the window
void init_game(t_game *game)
{
    int window_width;
    int window_height;

    // Initialize the MiniLibX instance
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        write(2, "Error initializing MLX\n", 23);
        exit(1);
    }

    // Calculate window dimensions based on the map size
    window_width = game->map.width * TILE_SIZE;
    window_height = game->map.height * TILE_SIZE;

    // Create the game window
    game->win = mlx_new_window(game->mlx, window_width, window_height, "so_long");
    if (!game->win)
    {
        write(2, "Error creating window\n", 22);
        exit(1);
    }
}

// Load game images (sprites)
void init_images(t_game *game)
{
    int img_width;
    int img_height;

    game->img_wall = mlx_xpm_file_to_image(game->mlx, "image/wall.xpm", &img_width, &img_height);
    game->img_floor = mlx_xpm_file_to_image(game->mlx, "image/floor.xpm", &img_width, &img_height);
    game->img_player = mlx_xpm_file_to_image(game->mlx, "image/player.xpm", &img_width, &img_height);
    game->img_collectible = mlx_xpm_file_to_image(game->mlx, "image/gold.xpm", &img_width, &img_height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "image/exit.xpm", &img_width, &img_height);

    if (!game->img_wall || !game->img_floor || !game->img_player || !game->img_collectible || !game->img_exit)
    {
        write(2, "Error loading images\n", 21);
        exit(1);
    }
}

// Render the map and objects
void render_map(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            int screen_x = x * TILE_SIZE;
            int screen_y = y * TILE_SIZE;

            // Draw floor
            mlx_put_image_to_window(game->mlx, game->win, game->img_floor, screen_x, screen_y);

            // Draw wall
            if (game->map.map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, screen_x, screen_y);

            // Draw collectibles
            if (game->map.map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, screen_x, screen_y);

            // Draw exit
            if (game->map.map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->img_exit, screen_x, screen_y);

            // Draw player
            if (game->map.map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, screen_x, screen_y);

            x++;
        }
        y++;
    }
}

// Handle key presses
int handle_keypress(int keysym, t_game *game)
{
    if (keysym == XK_Escape)
    {
        cleanup_game(game);
        exit(0);
    }
    // Handle movement keys (WASD)
    if (keysym == XK_w || keysym == XK_W)
        move_player(game, 0, -1); // Move up
    else if (keysym == XK_s || keysym == XK_S)
        move_player(game, 0, 1);  // Move down
    else if (keysym == XK_a || keysym == XK_A)
        move_player(game, -1, 0); // Move left
    else if (keysym == XK_d || keysym == XK_D)
        move_player(game, 1, 0);  // Move right

    return (0);
}

// Move player function
void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->map.player_x + dy;
    int new_y = game->map.player_y + dx;

    // Check for wall collision
    if (game->map.map[new_x][new_y] == '1')
        return;

    // Check for exit without all collectibles
    if (game->map.map[new_x][new_y] == 'E' && game->map.collectibles > 0)
    {
        write(1, "Collect all collectibles before exiting!\n", 41);
        return;
    }

    // Check for exit with all collectibles collected
    if (game->map.map[new_x][new_y] == 'E' && game->map.collectibles == 0)
    {
        write(1, "You win!\n", 9);
        cleanup_game(game);
        exit(0);
    }

    // Collect collectible
    if (game->map.map[new_x][new_y] == 'C')
    {
        game->map.collectibles--;
        game->map.map[new_x][new_y] = '0';
    }

    // Update player position
    game->map.map[game->map.player_x][game->map.player_y] = '0';
    game->map.map[new_x][new_y] = 'P';
    game->map.player_x = new_x;
    game->map.player_y = new_y;

    // Render updated map
    render_map(game);
}

// Clean up resources
void cleanup_game(t_game *game)
{
    // Destroy images if they were created
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
    if (game->img_collectible)
    {
        mlx_destroy_image(game->mlx, game->img_collectible);
        game->img_collectible = NULL;
    }
    if (game->img_exit)
    {
        mlx_destroy_image(game->mlx, game->img_exit);
        game->img_exit = NULL;
    }

    // Destroy window if it was created
    if (game->win)
    {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
    }

    // Destroy display (Linux specific)
    #ifdef __linux__
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
    }
    #endif

    // Free the mlx instance
    if (game->mlx)
    {
        free(game->mlx);
        game->mlx = NULL;
    }

    // Free the map
    if (game->map.map)
    {
        free_map(game->map.map, game->map.height);
        game->map.map = NULL;
    }
}

// Handle window close event
int handle_close(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}

// Game loop function (optional if you need continuous updates)
int game_loop(t_game *game)
{
    // You can perform animations or other updates here
    render_map(game);
    return (0);
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        write(2, "Usage: ./so_long <map_file>\n", 28);
        return (1);
    }

    // Initialize game structure to zero
    ft_memset(&game, 0, sizeof(t_game));

    // Load the map and perform error handling
    if (!load_map(argv[1], &game.map))
    {
        write(2, "Error loading map\n", 18);
        return (1);
    }

    // Check for valid path using flood fill
    if (!check_path(game.map.map, game.map.height, game.map.width, game.map.player_x, game.map.player_y, game.map.collectibles))
    {
        free_map(game.map.map, game.map.height);
        return (1);
    }

    // Initialize MLX and create window
    init_game(&game);

    // Load game images
    init_images(&game);

    // Render the initial map
    render_map(&game);

    // Set up hooks
    mlx_hook(game.win, ClientMessage, StructureNotifyMask, handle_close, &game);
    mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);

    // Enter MLX loop
    mlx_loop(game.mlx);

    // Cleanup (this won't be reached if you call exit)
    cleanup_game(&game);

    return (0);
}