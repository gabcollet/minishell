#include "minishell.h"

void	ms_error_quote(t_parser *parser)
{
	if (parser->state == S_QUOTE)
	{
		ft_putstr_fd(ERR_QUOTE_S, 1);
		exit (-1);
	}
	else
	{
		ft_putstr_fd(ERR_QUOTE_D, 1);
		exit (-1);
	}
}