#include <stdio.h>

int		ft_printf(char *str, ... );

int		main(void)
{
	printf("%10.2s\n", "toto");
	ft_printf("%10.2s\n", "toto");
	printf("Magic %s is %5d\n", "number", 42);
	ft_printf("Magic %s is %5d\n", "number", 42);
	printf("Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	return (0);
}
