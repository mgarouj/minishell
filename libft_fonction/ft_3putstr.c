#include "../minishell.h"

void	ft_3putstr(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
        ft_putstr_fd(s1, 1);
	if (s2)
        ft_putstr_fd(s2, 1);
	if (s3)
        ft_putstr_fd(s3, 1);
	if (s4)
        ft_putstr_fd(s4, 1);
}
