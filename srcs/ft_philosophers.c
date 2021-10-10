#include "../include/philosophers.h"

int main(int ac, char **av)
{
    t_data  *data;

    if (ac != 5 && ac != 6)
        ft_putstr_fd("Error: Wrong number of argument\n", 2);
    else
    {
        data = ft_init(av, ac);
        if (!data)
            return (1);
        else
            ft_algo(data);
    }
    return (0);
}