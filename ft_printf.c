/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:48:17 by rkawahar          #+#    #+#             */
/*   Updated: 2024/05/27 19:10:46 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_address(unsigned long address)
{
	int	ans;

	ans = 2;
	write(1, "0x", 2);
	ans += ft_to_hexaddress(address, 0);
	return (ans);
}

int	ft_mini_printf(const char *str, size_t i, va_list ap)
{
	if (str[i] == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (str[i] == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (str[i] == 'p')
		return (ft_print_address(va_arg(ap, unsigned long int)));
	else if (str[i] == 'd' || str[i] == 'i')
		return (ft_print_itoa(va_arg(ap, int), 0));
	else if (str[i] == 'u')
		return (ft_print_uint(va_arg(ap, unsigned int), 0));
	else if (str[i] == 'x')
		return (ft_to_hex(va_arg(ap, int), 0));
	else if (str[i] == 'X')
		return (ft_to_upperhex(va_arg(ap, int), 0));
	else if (str[i] == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	ap;
	size_t	i;

	len = 0;
	i = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
			len += ft_mini_printf(str, ++i, ap);
		else
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(ap);
	return (len);
}
