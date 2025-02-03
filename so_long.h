/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:08:30 by root              #+#    #+#             */
/*   Updated: 2025/02/03 02:37:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>
#include <time.h>
# include "mlx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define WALL '1'
# define EMPTY '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define VISITED 'V'
# define TILE_SIZE 32


int			checknewline(char *str);
char		*get_next_line(int fd);

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		players_num;
	int		player_moves;
	int		collectibles;
	int		moves;
	int		exit_x;
	int		exit_y;
	int		img_width;
	int		img_height;
	int		exit_num;
	int		exit_reachable;
	void	*wall_img;
	void	*empty_img;
	void	*collectible_img;
	void	*exit_img;
	void	*player_img;
}			t_game;


void		game_init(t_game *game);
void 		error_handle(t_game *game, char *line);

#endif