/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:28:50 by root              #+#    #+#             */
/*   Updated: 2025/02/28 01:00:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	destroy_game(t_game *game)
{
	int	i;

	i = 0;
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->empty_img);
	mlx_destroy_image(game->mlx, game->collectible_img);
	mlx_destroy_image(game->mlx, game->exit_img);
	mlx_destroy_image(game->mlx, game->player_img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(0);
	return (0);
}

void	load_textures(t_game *game)
{
	int	img_width;
	int	img_height;

	img_width = TILE_SIZE;
	img_height = TILE_SIZE;
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&img_width, &img_height);
	game->empty_img = mlx_xpm_file_to_image(game->mlx, "textures/empty.xpm",
			&img_width, &img_height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&img_width, &img_height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&img_width, &img_height);
	if (!game->wall_img || !game->empty_img || !game->collectible_img
		|| !game->exit_img || !game->player_img)
		error_handle(game, "Failed to load textures");
}

void	apply_textures(t_game *game, int x, int y)
{
	if (game->map[y][x] == WALL)
		mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x
			* TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == EMPTY)
		mlx_put_image_to_window(game->mlx, game->win, game->empty_img, x
			* TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == COLLECTIBLE)
		mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, x
			* TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == EXIT)
		mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x
			* TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == PLAYER)
		mlx_put_image_to_window(game->mlx, game->win, game->player_img, x
			* TILE_SIZE, y * TILE_SIZE);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			apply_textures(game, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

void	fix_line(t_game *game, int i)
{
	if (ft_strlen(game->map[i]) == 0)
		error_handle(game, "Empty line in map");
	if (game->map[i][ft_strlen(game->map[i]) - 1] == '\n')
		game->map[i][ft_strlen(game->map[i]) - 1] = 0;
}
