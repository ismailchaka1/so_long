/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:54:59 by root              #+#    #+#             */
/*   Updated: 2025/02/28 00:59:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_data(t_game *game)
{
	game->player_moves = 0;
	game->moves = 0;
	game->exit_reachable = 0;
	game->players_num = 0;
	game->collectibles = 0;
	game->exit_num = 0;
}

void	set_player(t_game *game, int i, int j)
{
	if (game->map[i][j] == PLAYER)
	{
		game->player_x = j;
		game->player_y = i;
		game->players_num++;
	}
}

void	set_exit(t_game *game, int i, int j)
{
	if (game->map[i][j] == EXIT)
	{
		game->exit_x = j;
		game->exit_y = i;
		game->exit_num++;
	}
}

void	check_collectibles(t_game *game)
{
	if (game->players_num != 1 || game->collectibles < 1 || game->exit_x == 0
		|| game->exit_y == 0 || game->exit_num != 1)
		error_handle(game, "Invalid map 2");
}

int	count_map_height(int fd)
{
	int		map_height;
	char	*line;

	map_height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strncmp(line, "\n", 2))
			map_height++;
		free(line);
	}
	return (map_height);
}
