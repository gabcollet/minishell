#include "minishell.h"

void printList(t_token *tok)
{
	int i = 0;
	while(tok)
	{
		printf("tok[%d] = %s\ntype = %u\n", i, tok->str_tok, tok->type);
		tok = tok->next;
		i++;
	}
}

int	counter_token(t_token *tok)
{
	int	i;

	i = 0;
	while(tok)
	{
		tok = tok->next;
		i++;
	}
	return (i);
}

char **token_to_tab(t_token *token)
{
	char **tab;
	int	i;
	int	counter;
	t_token *first;

	first = token;
	counter = counter_token(token);
	tab = (char**)ft_calloc(counter + 1, sizeof(char*));
	i = 0;
	while (first->next != NULL)
	{
		tab[i] = ft_calloc(ft_strlen(first->str_tok) + 1, sizeof(char*));
		ft_strlcpy(tab[i], first->str_tok, ft_strlen(first->str_tok) + 1);
		first = first->next;
		//printf("%s\n", tab[i]);
		i++;
	}
	return (tab);
}
	
char	**ms_parsing(char *line)
{
	char	*temp;
	char 	**tab;
	t_parser *parser;
	t_token *first;
	t_token *first2;
	t_token *token;

	token = ms_token_newlst(NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	first = token;
	first2 = token;
	temp = ms_trim_space(line);
	while (!empty_str(temp))
	{
		temp = ms_init_s_parser(parser, temp);
		if (ms_get_token(parser, token))
		{
			ms_add_tok_to_lst(parser, token);
			token = token->next;
			temp = ms_get_next_tok(parser, temp);
		}
	}
	token = ms_check_syntax(first);
	tab = token_to_tab(first);
	//printList(first2);
	free(temp);
	free(parser);
	free_token_lst(first);
	return (tab);
}

bool empty_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	if (i > 0)
		return (false);
	return (true);
}

char *ms_trim_space(char *str)
{
	char *temp;
	char *temp1;

	temp = ft_strdup(str);
	temp1 = temp;
	temp1 = ft_strtrim(temp, WHITESPACE);
	free(temp);
	return (temp1);
}