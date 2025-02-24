/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:10 by root              #+#    #+#             */
/*   Updated: 2025/02/18 20:14:00 by root             ###   ########.fr       */
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

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

void	flood_fill(char **map, int x, int y, int *collectibles, t_game *game)
{
	char	current_tile;

	// Base cases
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return ; // Out of bounds
	if (map[y][x] == WALL || map[y][x] == VISITED)
		return ; // Wall or already visited
	// Mark the tile as visited
	current_tile = map[y][x];
	map[y][x] = VISITED;
	// Check if the tile is a collectible or exit
	if (current_tile == COLLECTIBLE)
		(*collectibles)--;
	if (current_tile == EXIT)
		game->exit_reachable = 1;
	// Recursively explore neighboring tiles
	flood_fill(map, x + 1, y, collectibles, game); // Right
	flood_fill(map, x - 1, y, collectibles, game); // Left
	flood_fill(map, x, y + 1, collectibles, game); // Down
	flood_fill(map, x, y - 1, collectibles, game); // Up
}
void	validate_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		collectibles;

	collectibles = game->collectibles;
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
	flood_fill(map_copy, game->player_x, game->player_y, &collectibles, game);
	free_mapcopy(map_copy);
	if (collectibles != 0)
		error_handle(game, "Collectibles are not reachable");
	else if (game->exit_reachable != 1)
		error_handle(game, "Exit is not reachable");
	else
		game_init(game);
}

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

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != WALL && game->map[i][j] != EMPTY
				&& game->map[i][j] != PLAYER && game->map[i][j] != COLLECTIBLE
				&& game->map[i][j] != EXIT)
				error_handle(game, "Invalid map 1");
			if (game->map[i][j] == PLAYER)
			{
				game->player_x = j;
				game->player_y = i;
				game->players_num++;
			}
			if (game->map[i][j] == COLLECTIBLE)
				game->collectibles++;
			if (game->map[i][j] == EXIT)
			{
				game->exit_num++;
				game->exit_x = j;
				game->exit_y = i;
			}
			j++;
		}
		i++;
	}
	if (game->players_num != 1 || game->collectibles < 1 || game->exit_x == 0
		|| game->exit_y == 0 || game->exit_num != 1)
		error_handle(game, "Invalid map 2");
	validate_map(game);
}

int	count_map_height(int fd)
{
	int		map_height;
	char	*line;

	map_height = 0;
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, "\n", 2))
			map_height++;
		free(line);
	}
	return (map_height);
}

void	fixLine(t_game *game, int i)
{
	if (game->map[i][ft_strlen(game->map[i]) - 1] == '\n')
		game->map[i][ft_strlen(game->map[i]) - 1] = 0;
	if (ft_strlen(game->map[i]) == 0)
		error_handle(game, "Empty line in map");
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
		fixLine(game, i);
		free(line);
		if (game->map_width == 0)
			game->map_width = ft_strlen(game->map[i]);
		else if (ft_strlen(game->map[i]) != (size_t)game->map_width)
		{
			free_map(game);
			printf("Error: Map is not rectangular\n");
			exit(1);
		}
		i++;
	}
	close(fd);
}

void	handle_file_error(int fd, char *message)
{
	if (fd == -1)
	{
		perror(message);
		exit(1);
	}
}

void	readMap(char *map)
{
	t_game	game;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		handle_file_error(fd, "MAP NOT FOUND");
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
		handle_file_error(fd, "MAP NOT FOUND");
	}
	read_map_data(fd, &game);
	check_map(&game);
}

int	main(int ac, char **av)
{
	int filelen;

	if (ac != 2)
		return (0);
	filelen = ft_strlen(av[1]);
	if (filelen < 5)
		return (0);
	if (av[1][filelen] == '\0' && av[1][filelen - 1] == 'r' && av[1][filelen
		- 2] == 'e' && av[1][filelen - 3] == 'b' && av[1][filelen - 4] == '.')
	{
		readMap(av[1]);
	}
	else
		return (0);
	return (1);
}