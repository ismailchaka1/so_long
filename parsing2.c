/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:51:46 by root              #+#    #+#             */
/*   Updated: 2025/02/28 01:23:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_handle(t_game *game, char *line)
{
	int	i;

	printf("Error: %s\n", line);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	exit(1);
}

void	free_mapcopy(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_map(t_game *game, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(game->map[j]);
		j++;
	}
	free(game->map);
	game->map = NULL;
}

void	flood_fill(char **map, int x, int y, t_flood_fill_data *data)
{
	char	current_tile;

	if (x < 0 || y < 0)
		return ;
	if (map[y][x] == WALL || map[y][x] == VISITED)
		return ;
	current_tile = map[y][x];
	map[y][x] = VISITED;
	if (current_tile == COLLECTIBLE)
		data->collectibles--;
	if (current_tile == EXIT)
	{
		data->exit_reachable = 1;
		return ;
	}
	flood_fill(map, x + 1, y, data);
	flood_fill(map, x - 1, y, data);
	flood_fill(map, x, y + 1, data);
	flood_fill(map, x, y - 1, data);
}

void	validate_path(t_game *game)
{
	char				**map_copy;
	int					i;
	t_flood_fill_data	data;

	data.collectibles = game->collectibles;
	data.exit_reachable = game->exit_reachable;
	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		exit(1);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		i++;
	}
	map_copy[i] = NULL;
	flood_fill(map_copy, game->player_x, game->player_y, &data);
	free_mapcopy(map_copy);
	game->exit_reachable = data.exit_reachable;
	if (data.collectibles != 0)
		error_handle(game, "Collectibles are not reachable");
	else if (game->exit_reachable != 1)
		error_handle(game, "Exit is not reachable");
	else
		game_init(game);
}
