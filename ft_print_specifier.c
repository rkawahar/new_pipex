/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:19:34 by rkawahar          #+#    #+#             */
/*   Updated: 2024/05/27 19:12:31 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_print_itoa(int num, int len)
{
	char	tmp;

	if (num == -2147483648)
		return (write(1, "-2147483648", 11));
	if (num == 0)
		return (write(1, "0", 1));
	else if (num < 0)
	{
		write(1, "-", 1);
		len = ft_print_itoa(-num, ++len);
		return (len);
	}
	else if (9 < num)
	{
		tmp = '0' + (num % 10);
		len = ft_print_itoa(num / 10, ++len);
		write(1, &tmp, 1);
		return (len);
	}
	else
	{
		tmp = '0' + (num);
		write(1, &tmp, 1);
		return (++len);
	}
}

int	ft_print_uint(unsigned int num, int len)
{
	char	tmp;

	if (num == 0)
		return (write(1, "0", 1));
	else if (9 < num)
	{
		tmp = '0' + num % 10;
		len = ft_print_uint(num / 10, ++len);
		write(1, &tmp, 1);
		return (len);
	}
	else
	{
		tmp = '0' + num;
		write(1, &tmp, 1);
		return (++len);
	}
}

int	ft_to_hexaddress(unsigned long int num, int len)
{
	const char	base[16] = "0123456789abcdef";

	if (num == 0)
		return (write(1, "0", 1));
	else if (num < 0)
	{
		write(1, "-", 1);
		return (ft_to_hexaddress(-num, ++len));
	}
	else if (15 < num)
	{
		len = ft_to_hexaddress(num / 16, ++len);
		write(1, &base[num % 16], 1);
		return (len);
	}
	else
	{
		write(1, &base[num], 1);
		return (++len);
	}
}

int	ft_to_hex(unsigned int num, int len)
{
	const char	base[16] = "0123456789abcdef";

	if (num == 0)
		return (write(1, "0", 1));
	else if (num < 0)
	{
		write(1, "-", 1);
		return (ft_to_hex(-num, ++len));
	}
	else if (15 < num)
	{
		len = ft_to_hex(num / 16, ++len);
		write(1, &base[num % 16], 1);
		return (len);
	}
	else
	{
		write(1, &base[num], 1);
		return (++len);
	}
}

int	ft_to_upperhex(unsigned int num, int len)
{
	const char	base[16] = "0123456789ABCDEF";

	if (num == 0)
		return (write(1, "0", 1));
	else if (num < 0)
	{
		write(1, "-", 1);
		return (ft_to_upperhex(-num, ++len));
	}
	else if (15 < num)
	{
		len = ft_to_upperhex(num / 16, ++len);
		write(1, &base[num % 16], 1);
		return (len);
	}
	else
	{
		write(1, &base[num], 1);
		return (++len);
	}
}
