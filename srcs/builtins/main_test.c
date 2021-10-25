#include "minishell.h"

t_msh g_msh;

int main(int ac, char** av, char **env)
{
/* 	char c; */
	(void)ac;
	(void)av;
	ms_dup_env(env);
	ms_init_export();
	ms_export(av + 1);
	/* ms_env() */
/* 	scanf("%c", &c); */
	ms_unset(av + 2);
	ms_env();
	ft_free_tab(g_msh.env);
	ft_free_tab(g_msh.env_export);
}
