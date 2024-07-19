#include "libft.h"

int	fd_putnbr_u(int fd, unsigned int nb)
{
	int		length;
	char	c;

	length = 0;
	if (nb == 2147483648)
		return (length += fd_putstr(fd, "2147483648"));
	if (nb >= 10)
		length += fd_putnbr (fd, nb / 10);
	c = (nb % 10) + 48;
	length += fd_putchar(fd, c);
	return (length);
}
