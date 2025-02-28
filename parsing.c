/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:59:07 by root              #+#    #+#             */
/*   Updated: 2025/02/28 00:59:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (i == 0 || i == game->map_height - 1 || j == 0
				|| j == game->map_width - 1)
			{
				if (game->map[i][j] != WALL)
					error_handle(game, "Map is not surrounded by walls");
			}
			if (!ft_strchr("01CEP", game->map[i][j]))
				error_handle(game, "Invalid character in map");
			j++;
		}
		i++;
	}
	validate_path(game);
}

void	check_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	initialize_data(game);
	while (++i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != WALL && game->map[i][j] != EMPTY
				&& game->map[i][j] != PLAYER && game->map[i][j] != COLLECTIBLE
				&& game->map[i][j] != EXIT)
				error_handle(game, "Invalid map 1");
			if (game->map[i][j] == PLAYER)
				set_player(game, i, j);
			if (game->map[i][j] == COLLECTIBLE)
				game->collectibles++;
			if (game->map[i][j] == EXIT)
				set_exit(game, i, j);
			j++;
		}
	}
	check_collectibles(game);
	validate_map(game);
}

void	read_map_data(int fd, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	game->map_width = 0;
	game->map[game->map_height] = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map[i] = ft_strdup(line);
		free(line);
		fix_line(game, i);
		if (game->map_width == 0)
			game->map_width = ft_strlen(game->map[i]);
		else if (ft_strlen(game->map[i]) != (size_t)game->map_width)
		{
			free_map(game, i);
			printf("Error: Map is not rectangular\n");
			exit(1);
		}
		i++;
	}
	close(fd);
}

void	read_map(char *map)
{
	t_game	game;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		exit(1);
	game.map_height = count_map_height(fd);
	game.map = malloc(sizeof(char *) * (game.map_height + 1));
	if (!game.map)
	{
		perror("Malloc failed");
		exit(1);
	}
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		free(game.map);
		exit(1);
	}
	read_map_data(fd, &game);
	check_map(&game);
}

int	main(int ac, char **av)
{
	int	filelen;

	if (ac != 2)
		return (0);
	filelen = ft_strlen(av[1]);
	if (filelen < 5)
		return (0);
	if (av[1][filelen] == '\0' && av[1][filelen - 1] == 'r' && av[1][filelen
		- 2] == 'e' && av[1][filelen - 3] == 'b' && av[1][filelen - 4] == '.')
	{
		read_map(av[1]);
	}
	else
		return (0);
	return (1);
}
