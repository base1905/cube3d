/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 11:07:31 by ngonzo            #+#    #+#             */
/*   Updated: 2020/09/17 11:45:48 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	g_result;
int	g_wid;
int	g_pre;

static void		ft_putchar(char c)
{
	write(1, &c, 1);
	g_result++;
}

static void		ft_putstr(char *str, int len)
{
	int	i = 0;
	while (len > 0 && str[i] != '\0')
	{
		ft_putchar(str[i]);
		len--;
		i++;
	}
}

static int		ft_strlen(char *str)
{
	int	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static char		*ft_itoa(unsigned long nbr, int base)
{
	unsigned long	tmp_nbr = nbr;
	int	len = 0;
	if (nbr == 0)
		len++;
	while (tmp_nbr > 0)
	{
		tmp_nbr /= base;
		len++;
	}
	char *tmp = NULL;
	if (!(tmp = malloc(sizeof(char *) * (len + 1))))
		return (0);
	tmp[len] = '\0';
	while (len > 0)
	{
		tmp[len - 1] = nbr % base;
		if (nbr % base > 9)
			tmp[len - 1] += 'a' - 10;
		else
			tmp[len - 1] += 48;
		nbr /= base;
		len--;
	}
	return (tmp);
}

static void		ft_printf_s(char *str)
{
	int	len = ft_strlen(str);
	if (g_pre != -1 && g_pre < len)
		len = g_pre;
	while (g_wid > len)
	{
		ft_putchar(' ');
		g_wid--;
	}
	ft_putstr(str, len);
}

static void		ft_printf_x(unsigned int nbr)
{
	char *str = ft_itoa(nbr, 16);
	int	len = ft_strlen(str);
	int	tmp_len = len;
	if (g_pre != -1 && g_pre > len)
		len = g_pre;
	while (g_wid > len)
	{
		ft_putchar(' ');
		g_wid--;
	}
	while (len > tmp_len)
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, tmp_len);
}

static void		ft_printf_d(int nbr)
{
	int sign = 0;
	if (nbr < 0)
	{
		sign = 1;
		nbr *= -1;
	}
	char *str = ft_itoa(nbr, 10);
	int	len = ft_strlen(str);
	int	tmp_len = len;
	if (g_pre != -1 && g_pre > len)
		len = g_pre;
	if (sign == 1)
		g_wid--;
	while (g_wid > len)
	{
		ft_putchar(' ');
		g_wid--;
	}
	if (sign == 1)
		ft_putchar('-');
	while (len > tmp_len)
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, tmp_len);
}

int		ft_printf(const char *str, ... )
{
	int i = 0;
	va_list	ap;
	g_result = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			g_wid = 0;
			g_pre = -1;
			while (str[i] >= '0' && str[i] <= '9')
			{
				g_wid = g_wid * 10 + ( str[i] - 48);
				i++;
			}
			if ( str[i] == '.')
			{
				i++;
				g_pre = 0;
				while (str[i] >= '0' && str[i] <= '9')
				{
					g_pre = g_pre * 10 + (str[i] - 48);
					i++;
				}
			}
			if ( str[i] == 's')
				ft_printf_s(va_arg(ap, char *));
			else if (str[i] == 'x')
				ft_printf_x(va_arg(ap, unsigned int));
			else if (str[i] == 'd')
				ft_printf_d(va_arg(ap, int));
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (g_result);
}
