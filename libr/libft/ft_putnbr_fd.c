/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:54:40 by nhayoun           #+#    #+#             */
/*   Updated: 2024/04/25 12:13:14 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libr.h"

void	put_nbr(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		put_nbr(n, fd);
	}
	else if (n < 10)
		ft_putchar_fd((n + '0'), fd);
	else
	{
		put_nbr((n / 10), fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
		put_nbr(n, fd);
}
