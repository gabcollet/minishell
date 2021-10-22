#include "minishell.h"



t_token *ms_addnew_token(t_token *tok, char *temp)
{
	tok = malloc(sizeof(*tok));
	if (!tok)
		return (NULL);
	tok->str_tok = ft_strdup(temp);
	tok->next = NULL;
	tok->type = STRING; //fonction qui renvoit le bon type
	ms_token_addback(&tok, ms_token_new(NULL));
	free(temp);
	return (tok);
}

void	ms_add_tok_to_list(t_token *tok, char *temp)
{
	tok->str_tok = ft_strdup(temp);
	ms_token_addback(&tok, ms_token_new(NULL));

}


void	ms_token_addback(t_token **token, t_token *new_tok)
{
	t_token *last_tok;

	if (*token == NULL)
		*token = new_tok;
	else
	{
		last_tok = ms_token_last(*(token));
		last_tok->next = new_tok;
		last_tok->previous = last_tok;
	}
}

t_token	*ms_token_last(t_token	*token)
{
	if (token)
	{
		while (token->next)
			token = token->next;
	}
	return (token);
}

t_token	*ms_token_new(void	*token)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->str_tok = token;
	new->type = VOID;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}