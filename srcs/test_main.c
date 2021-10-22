#include "minishell.h"

t_msh g_msh = {0};


int main (void)
{
	t_parser *parser = NULL;
	t_token *token = NULL;

	char *line;
	parser = ft_calloc(1, sizeof(t_parser));
	line = readline("TEST: ");
	ms_parsing(line, parser, token);
	
}