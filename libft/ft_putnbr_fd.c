/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:45:00 by ichakank          #+#    #+#             */
/*   Updated: 2025/01/30 04:07:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	number;

	number = n;
	if (fd > 0)
	{
		if (number < 0)
		{
			number *= -1;
			ft_putchar_fd('-', fd);
		}
		if (number >= 10)
			ft_putchar_fd(number % 10 + '0', fd);
		ft_putnbr_fd(number / 10, fd);
	}
}
