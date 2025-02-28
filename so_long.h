/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:08:30 by root              #+#    #+#             */
/*   Updated: 2025/02/28 01:21:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

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

typedef struct s_flood_fill_data
{
	int		exit_reachable;
	int		collectibles;
}			t_flood_fill_data;

void		game_init(t_game *game);
void		error_handle(t_game *game, char *line);

int			destroy_game(t_game *game);
void		load_textures(t_game *game);
void		apply_textures(t_game *game, int x, int y);
void		move_player(t_game *game, int new_x, int new_y);
int			close_window(t_game *game);
int			render_map(t_game *game);
void		validate_path(t_game *game);
void		flood_fill(char **map, int x, int y, t_flood_fill_data *data);
void		free_mapcopy(char **map);
void		free_map(t_game *game, int i);
void		initialize_data(t_game *game);
void		set_player(t_game *game, int i, int j);
void		set_exit(t_game *game, int i, int j);
void		check_collectibles(t_game *game);
int			count_map_height(int fd);
void		validate_map(t_game *game);
void		check_map(t_game *game);
void		read_map_data(int fd, t_game *game);
void		fix_line(t_game *game, int i);
void		read_map(char *map);
int			key_press(int keycode, t_game *game);
int			destroy_game(t_game *game);
void		load_textures(t_game *game);
void		apply_textures(t_game *game, int x, int y);
int			render_map(t_game *game);
#endif