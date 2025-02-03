/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:28:50 by root              #+#    #+#             */
/*   Updated: 2025/02/03 02:38:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


void load_textures(t_game *game)
{
    int img_width = TILE_SIZE;
    int img_height = TILE_SIZE;

    game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &img_width, &img_height);
    game->empty_img = mlx_xpm_file_to_image(game->mlx, "textures/empty.xpm", &img_width, &img_height);
    game->collectible_img = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &img_width, &img_height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &img_width, &img_height);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &img_width, &img_height);

    if (!game->wall_img || !game->empty_img || !game->collectible_img || !game->exit_img || !game->player_img)
        error_handle(game, "Failed to load textures");
}


int render_map(t_game *game)
{
    int x, y;

    for (y = 0; y < game->map_height; y++)
    {
        for (x = 0; x < game->map_width; x++)
        {
            if (game->map[y][x] == WALL)
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == EMPTY)
                mlx_put_image_to_window(game->mlx, game->win, game->empty_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == COLLECTIBLE)
                mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == EXIT)
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == PLAYER)
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    return (0);
}

void move_player(t_game *game, int new_x, int new_y)
{
    printf("new_x: %d, new_y: %d\n", new_x, new_y);
    if (game->map[new_y][new_x] == WALL)
        return;

    if (game->map[new_y][new_x] == COLLECTIBLE)
        game->collectibles--;

    if (game->map[new_y][new_x] == EXIT && game->collectibles == 0)
        printf("You win!\n");
        // exit_with_success("You win!");

    game->map[game->player_y][game->player_x] = EMPTY;
    game->map[new_y][new_x] = PLAYER;
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
    printf("Moves: %d\n", game->moves);
    render_map(game);
}

int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == 65307)
        printf("ESC pressed\n");
        // close_window(game);
    else if (keycode == 119 || keycode == 65362)
        move_player(game, game->player_x, game->player_y - 1);
    else if (keycode == 65364 || keycode == 115)
        move_player(game, game->player_x, game->player_y + 1);
    else if (keycode == 65361 || keycode == 97)
        move_player(game, game->player_x - 1, game->player_y);
    else if (keycode == 65363 || keycode == 100)
        move_player(game, game->player_x + 1, game->player_y);
    return (0);
}
void delay(int milliseconds)
{
    clock_t start_time = clock();
    clock_t end_time = milliseconds * CLOCKS_PER_SEC / 1000 + start_time;
    while (clock() < end_time)
    {
        // Busy-waiting
    }
}

void zwa9_dzob(t_game *game)
{
    int i = 0;
    char *line;
    while (1)
    {
        line = ft_strjoin("Loading ", ft_itoa(i));
        mlx_clear_window(game->mlx, game->win);
        mlx_string_put(game->mlx, game->win, 32, 32, 0xFFF, line);
        i++;
        free(line);
        if (i == 50)
            break;
        delay(80);
    }
    delay(700);
    mlx_clear_window(game->mlx, game->win);
    mlx_string_put(game->mlx, game->win, 32, 32, 0xFFF, "Loading 100");
    delay(500);
}

void	game_init(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, game->map_width * 32, game->map_height * 32, "so_long");
    game->player_moves = 0;
    game->moves = 0;
    game->exit_reachable = 0;
    load_textures(game);
    zwa9_dzob(game);
    render_map(game);
    mlx_loop_hook(game->mlx, &render_map, game);
    mlx_hook(game->win, 2, 1L << 0, &key_press, game);
    mlx_loop(game->mlx);
}

// void	game_init(t_game *game)
// {
//     game->mlx = mlx_init();
//     game->win = mlx_new_window(game->mlx, game->map_width * 32, game->map_height * 32, "so_long");
//     game->player_moves = 0;
//     game->moves = 0;
//     game->exit_reachable = 0;
//     load_textures(game);
//     render_map(game);
//     mlx_loop_hook(game->mlx, &render_map, game);
//     mlx_hook(game->win, 2, 1L << 0, &key_press, game);
//     mlx_loop(game->mlx);
// }
