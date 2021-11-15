#include "minishell.h"

/*créer et initialise une nouvelle liste chainée job*/
t_job	*ms_job_newlst(void)
{
	t_job	*new;

	new = malloc(sizeof(t_job) * 1);
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->next = NULL;
	new->file = NULL;
	return (new);
}

/*positionne le pointeur sur le dernier node de la liste chainée job*/
t_job	*ms_job_last(t_job *job)
{
	while (job)
	{
		if (job->next == NULL)
			return (job);
		job = job->next;
	}
	return (job);
}

/*ajoute un nouveau node à la suite du dernier node de la liste job*/
void	ms_job_addback(t_job **job, t_job *new_job)
{
	t_job *last_job;

	if (*job == NULL)
		*job = new_job;
	else
	{
		last_job = ms_job_last(*job);
		last_job->next = new_job;
		new_job->previous = last_job;
	}
}