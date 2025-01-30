/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:08:30 by root              #+#    #+#             */
/*   Updated: 2025/01/30 01:04:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		checknewline(char *str);
char	*get_next_line(int fd);


typedef struct s_game {
    void *mlx;
    void *win;
    char **map;
    int map_width;
    int map_height;
    int player_x;
    int player_y;
    int players_num;
    int player_moves;
    int collectibles;
    int moves;
    int exit_x;
    int exit_y;
    int img_width;
    int img_height;
    void *wall_img;
    void *empty_img;
    void *collectible_img;
    void *exit_img;
    void *player_img;
} t_game;

#endif