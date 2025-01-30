/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:10 by root              #+#    #+#             */
/*   Updated: 2025/01/30 04:00:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_handle(t_game *game, char *line)
{
    printf("Error %s \n", line);
    int i = 0;
    while (i <= game->map_height)
    {
        free(game->map[i]);
        i++;
    }
    free(game->map);
    exit(1);
}
void validate_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (i == 0 || i == game->map_height - 1 || j == 0 || j == game->map_width - 1)
            {
                if (game->map[i][j] != '1')
                    error_handle(game, "Map is not surrounded by walls");
            }
            if (!ft_strchr("01CEP", game->map[i][j]))
                error_handle(game, "Invalid character in map");

            j++;
        }
        i++;
    }
    error_handle(game, "Map is valid");
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
			if (game->map[i][j] != '1' && game->map[i][j] != '0'
				&& game->map[i][j] != 'P' && game->map[i][j] != 'C'
				&& game->map[i][j] != 'E')
				error_handle(game, "Invalid map");
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				game->players_num++;
			}
			if (game->map[i][j] == 'C')
				game->collectibles++;
			if (game->map[i][j] == 'E')
			{
				game->exit_x = j;
				game->exit_y = i;
			}
			j++;
		}
		i++;
	}
	if (game->players_num != 1 || game->collectibles < 1 || game->exit_x == 0
		|| game->exit_y == 0)
		error_handle(game, "Invalid map");
	validate_map(game);
}

void readMap(char *map)
{
    t_game game;
    int i;
    int map_height;
    int fd;
    char *line;

    i = 0;
    fd = open(map, O_RDONLY);
    if (fd == -1)
    {
        perror("MAP NOT FOUND");
        exit(1);
    }
    map_height = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (ft_strncmp(line, "\n", 2))
            map_height++;
        free(line);
    }
    close(fd);

    game.map_height = map_height;
    game.map = malloc(sizeof(char *) * (map_height + 1));
    if (!game.map)
    {
        perror("Malloc failed");
        exit(1);
    }
    fd = open(map, O_RDONLY);
    if (fd == -1)
    {
        perror("MAP NOT FOUND");
        free(game.map);
        exit(1);
    }

    i = 0;
    game.map_width = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        game.map[i] = ft_strdup(line);
        if (game.map[i][ft_strlen(game.map[i]) - 1] == '\n')
            game.map[i][ft_strlen(game.map[i]) - 1] = 0;
        free(line);

        if (ft_strlen(game.map[i]) == 0)
        {
            error_handle(&game, "Empty line in map");
        }
        if (game.map_width == 0)
        {
            game.map_width = (int)ft_strlen(game.map[i]);
        }
        else if (ft_strlen(game.map[i]) != (size_t)game.map_width)
        {
            error_handle(&game, "Map is not rectangular");
        }

        i++;
    }
    game.map[i] = NULL;
    close(fd);
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