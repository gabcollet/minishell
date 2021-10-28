#include "minishell.h"

t_msh g_msh = {0};


int main(void)
{
	char *line;
	
	line = readline("TEST: ");
	ms_parsing(line);
	free(line);
}