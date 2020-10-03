/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arannara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:50:10 by arannara          #+#    #+#             */
/*   Updated: 2020/10/03 23:59:06 by arannara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int issymbol(int a)
{
	if ((a >= 33) && (a <= 126))
		return 1;
	else
		return 0;
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return(i);

}

int before ( char b )
{
	if 
}


int main(int argc, char *argv[])
{
	int i;
	char *str;
	int len;
	int count;
	int j;

	if (argc <= 2 || argc > 3)
		write(1, "\n", 1);
	else
	{
		i = 0;
		count = 0;

		str = argv[1];
		len = ft_strlen(argv[1]);

		while (++i < len)
		{	
			j = 0;
			while (++j < len)
			{
				if (str[i] == str[j] && i != j) 
					count++;
			}
			if (count > 0)
				write (1, &str[i], 1);
			count = 0;

		}
		printf("\nargv2 = %d", ft_strlen(argv[2]));
	}
	return(0);
}
https://github.com/alanbarrett2/42-Final-Exam/tree/master/2-0-union
