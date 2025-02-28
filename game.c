/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:28:50 by root              #+#    #+#             */
/*   Updated: 2025/02/28 00:50:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == WALL)
		return ;
	if (game->map[new_y][new_x] == COLLECTIBLE)
		game->collectibles--;
	if (game->map[new_y][new_x] == EXIT && game->collectibles == 0)
	{
		printf("YOU WIN\n");
		destroy_game(game);
	}
	if (game->map[new_y][new_x] == EXIT && game->collectibles != 0)
	{
		printf("YOU LOSE LOSER\n");
		destroy_game(game);
	}
	game->map[game->player_y][game->player_x] = EMPTY;
	game->map[new_y][new_x] = PLAYER;
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	printf("Moves: %d\n", game->moves);
	render_map(game);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		destroy_game(game);
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

void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_width * 32, game->map_height
			* 32, "so_long");
	game->player_moves = 0;
	game->moves = 0;
	game->exit_reachable = 0;
	load_textures(game);
	render_map(game);
	mlx_loop_hook(game->mlx, &render_map, game);
	mlx_hook(game->win, 2, 0, &key_press, game);
	mlx_hook(game->win, 17, 1L << 0, &destroy_game, game);
	mlx_loop(game->mlx);
}
