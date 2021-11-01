#include "minishell.h"

t_token *ms_check_syntax(t_token *token)
{
	t_token *first;
	char *temp;
	char *temp1;

	first = token;
	while (token)
	{
		if (token->type == STRING && ((token->str_tok[0] == '\'' || token->str_tok[0] == '\"')))
		{
			temp = ft_strdup(token->str_tok);
			free(token->str_tok);
			temp1 = ms_remove_quote(temp);
			token->str_tok = ft_strdup(temp1);
			free(temp);
			free(temp1);
		}
		token = token->next;
	}
	return (token);
}
