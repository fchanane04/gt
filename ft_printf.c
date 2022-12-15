/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanane <fchanane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:29:38 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/15 12:28:12 by fchanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdarg.h>
#include<unistd.h>

int	count;

void	ft_putchar(char c)
{
	write(1, &c, 1);
	count++;
}


void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = nbr * (-1);
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
}

void	ft_puthexa(unsigned int nb)
{
	char	*base = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_puthexa(nb / 16);
		ft_puthexa(nb % 16);
	}
	else
		ft_putchar(base[nb]);
}


void	ft_handle(char c, va_list ptr)
{
	if (c == 's')
		ft_putstr(va_arg(ptr, char *));
	if (c == 'd')
		ft_putnbr(va_arg(ptr, int));
	if (c == 'x')
		ft_puthexa(va_arg(ptr, unsigned int));
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		i;

	i = 0;
	count = 0;
	va_start(ptr, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_handle(str[i + 1], ptr);
			i++;
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(ptr);
	return (count);
}

#include<stdio.h>
int	main(int ac, char **av)
{
	printf("Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}