#include "minishell.h"

void	ms_parsing(char *line, t_parser *parser)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	parser->str_line = ft_strdup(line);
	temp = (char *)malloc(sizeof(char) * ft_strlen(line) + 1);
	/*
	setter ma structure avec un type en TEXT
	1 - trimmer les white spaces qui ne sont pas entre guillemets
	2- Tant que je ne rencontre pas un WS, un pipe ou une redir, je copie dans une temp que j'envoie dans ma struct token
		1 - Si je rencontre un ' ou ", je copie dans temp jusqu'à trouver la fermante
		2 - je substr str pour reprendre au prochain token
		  
	*/

	ft_strtrim(str, WHITESPACE);
	// je vérifie le type void check type()
	while ((!strchr(REDIRECTION, str[i]) && (!strchr(WHITESPACE, str[i]))
	{
		//si mon check type n'est pas sur TEXT, c'est que je suis tombée sur une " '
			// je vérifie que j'ai bien une guillemet fermante si non, message d'erreur
		temp[i] = str[i];
		i++;
	}
	//j'ajoute la temp à la liste chainée 


free(str);
free(temp);
}

void	