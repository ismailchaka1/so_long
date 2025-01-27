/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:10 by root              #+#    #+#             */
/*   Updated: 2025/01/27 18:11:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


void readMap(char *map)
{
    int fd = open(map, O_RDONLY);
    if (fd == -1)
    {
        perror("MAP NOT FOUND");
        exit(1);
    }
    char *line;
    while (get_next_line(fd, &line) > 0)
    {
        printf("%s\n", line);
        free(line);
    }
    printf("%s\n", line);
}

int main (int ac, char **av)
{
    if (ac != 2)
        return (0);
    readMap(ac[1]);
    return (1)
}