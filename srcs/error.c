#include "minishell.h"
#include "syntax.h"

void	ms_error_quote(t_parser *parser)
{
	if (parser->state == S_QUOTE)
		ft_putstr_fd(ERR_QUOTE_S, 1);
	else
		ft_putstr_fd(ERR_QUOTE_D, 1);
	g_msh.ret_exit = 1;
}

bool is_only_space(char *str)
{
    int    i;
    int space;

    i = 0;
    space = 0;
    while (str[i])
    {
        if (ft_strchr(WHITESPACE, str[i]))
            space++;
        i++;
    }
    if (space == i)
        return(true);
    return (false);
}
